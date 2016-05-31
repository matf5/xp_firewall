//if you use this code in a mfc program:
//add the header stdafx.h or disable precompiled header
//Unless you do it, when compiling  vc will say: Unexpected end 
//of file while looking for precompiled header

#include "stdafx.h"
#include "TDriver.h"


//Constructor. Initialize variables.
TDriver::TDriver(void)
{
	driverHandle = NULL;	   
	removable = TRUE;
	driverName = NULL;
	driverPath = NULL;
	driverDosName = NULL;
	initialized = FALSE;
	loaded = FALSE;
	started = FALSE;
}


//Destructor. Free resources and unload the driver.
TDriver::~TDriver(void)
{
	if(driverHandle != NULL)
	{
		CloseHandle(driverHandle); 
		driverHandle = NULL; 
	}
   
    UnloadDriver();
}

//If removable = TRUE, the driver isnt unload when exit
void TDriver::SetRemovable(BOOL value)
{
	removable = value;
}


//is driver initialized?
BOOL TDriver::IsInitialized(void)
{
	return initialized;
}

//is driver loaded?
BOOL TDriver::IsLoaded(void)
{
	return loaded;
}

//is driver started?
BOOL TDriver::IsStarted(void)
{
	return started;
}


//Init the driver class variables
DWORD TDriver::InitDriver(LPCTSTR path)
{
	//if already initialized, first unload
	if(initialized)
	{
		if(UnloadDriver() != DRV_SUCCESS)
			return DRV_ERROR_ALREADY_INITIALIZED;
	}

	//if yes, i analized the path to extract driver name
	driverPath = (LPTSTR)malloc(strlen(path) + 1);

	if(driverPath == NULL)
		return DRV_ERROR_MEMORY;

	strcpy(driverPath, path);
	//first i search the last backslash
	LPTSTR sPos1 = strrchr(driverPath, (int)'\\');

	//if null, the string havent any backslash
	if (sPos1 == NULL)
		sPos1 = driverPath;


	//now, i search .sys
	LPTSTR sPos2 = strrchr(sPos1, (int)'.');

	if (sPos2 == NULL || sPos1 > sPos2)
	{
		free(driverPath);
		driverPath = NULL;

		return DRV_ERROR_INVALID_PATH_OR_FILE;
	}
	//extract the driver name
	driverName = (LPTSTR) malloc (sPos2 - sPos1);
	
	if(driverName == NULL)
	{
		free(driverPath);
		driverPath = NULL;

		return DRV_ERROR_MEMORY;
	}

	memcpy(driverName, sPos1 + 1, sPos2 - sPos1 - 1);
	
	driverName[sPos2 - sPos1 - 1] = 0;

	//driverDosName = \\.\driverName 
	driverDosName = (LPTSTR) malloc (strlen(driverName) + 5);

	if(driverDosName == NULL)
	{
		free(driverPath);
		driverPath = NULL;
		free(driverName);
		driverName = NULL;
		return DRV_ERROR_MEMORY;
	}

	sprintf(driverDosName, "\\\\.\\%s", driverName);
		
	initialized = TRUE;
	return DRV_SUCCESS;
}


//Init the driver class variables
DWORD TDriver::InitDriver(LPCTSTR name, LPCTSTR path, LPCTSTR dosName)
{	
	//if already initialized, first unload
	if(initialized)
	{
		if(UnloadDriver() != DRV_SUCCESS)
			return DRV_ERROR_ALREADY_INITIALIZED;
	}

	LPTSTR dirBuffer;

	//if the user introduced path, first i will ckeck it
	if (path != NULL) 
	{
		//if yes, copy in auxiliar buffer and continue
		DWORD len = (DWORD)(strlen(name) + strlen(path) + 1);
		dirBuffer = (LPTSTR) malloc (len);

		if(dirBuffer == NULL)
			return DRV_ERROR_MEMORY;

		strcpy(dirBuffer, path);

	}

	else 
	{
		//if the user dont introduced path, i search in curren directory
		LPTSTR pathBuffer;
        DWORD len = GetCurrentDirectory(0, NULL);
      
		pathBuffer = (LPTSTR) malloc (len);

		if(pathBuffer == NULL)
			return DRV_ERROR_MEMORY;

		        
        if (GetCurrentDirectory(len, pathBuffer) != 0) 
		{
			len = (DWORD)(strlen(pathBuffer) + strlen(name) + 6);
			dirBuffer = (LPTSTR) malloc (len);

			if(dirBuffer == NULL)
			{
				free(pathBuffer);

				return DRV_ERROR_MEMORY;
			}

			//complete de total path, currentdirectory\driverName.sys
			sprintf(dirBuffer, "%s\\%s.sys", pathBuffer, name);

			//exists this file?
			if(GetFileAttributes(dirBuffer) == 0xFFFFFFFF)
			{
				free(pathBuffer);
				free(dirBuffer);

				//if no, i search in \system32\drivers\ 
				LPCTSTR sysDriver = "\\system32\\Drivers\\";
				LPTSTR sysPath;
	    	    
				//i have to get the windows directory
				DWORD len = GetWindowsDirectory(NULL, 0);
     			sysPath = (LPTSTR) malloc (len + strlen(sysDriver));

				if(sysPath == NULL)
					return DRV_ERROR_MEMORY;

				if (GetWindowsDirectory(sysPath, len) == 0) 
				{
					free(sysPath);
					
					return DRV_ERROR_UNKNOWN;
				}
	
				//complete the path and check it
				strcat(sysPath, sysDriver);
				len = (DWORD)(strlen(sysPath) + strlen(name) + 5);

				dirBuffer = (LPTSTR) malloc (len);

				if(dirBuffer == NULL)
					return DRV_ERROR_MEMORY;

				sprintf(dirBuffer, "%s%s.sys", sysPath, name);

				free(sysPath);

				//if the file neither exist, i dont know where is it -> i dont initialize
				if(GetFileAttributes(dirBuffer) == 0xFFFFFFFF)
				{
					free(dirBuffer);

					return DRV_ERROR_INVALID_PATH_OR_FILE;
				}
			}
        }

		else
		{
			free(pathBuffer);

			return DRV_ERROR_UNKNOWN;
		}
	}
	
	//Write driver's variables with obtained data
	driverPath = dirBuffer;

	driverName = (LPTSTR)malloc(strlen(name) + 1);

	if(driverName == NULL)
	{
		free(driverPath);
		driverPath = NULL;
		
		return DRV_ERROR_MEMORY;
	}

	strcpy(driverName, name);
	
	LPCTSTR auxBuffer;
	if(dosName != NULL)
        auxBuffer = dosName;
	
	else
		auxBuffer = name;

	//dosName=\\.\driverName
	if(auxBuffer[0] != '\\' && auxBuffer[1] != '\\')
	{
		driverDosName = (LPTSTR) malloc (strlen(auxBuffer) + 5);

		if(driverDosName == NULL)
		{
			free(driverPath);
			driverPath = NULL;

			free(driverName);
			driverName = NULL;

			return DRV_ERROR_MEMORY;
		}

		sprintf(driverDosName, "\\\\.\\%s", auxBuffer);
	}

	else
	{
		driverDosName = (LPTSTR) malloc (strlen(auxBuffer));

		if(driverDosName == NULL)
		{
			free(driverPath);
			driverPath = NULL;

			free(driverName);
			driverName = NULL;

			return DRV_ERROR_MEMORY;
		}

		strcpy(driverDosName, auxBuffer);
	}

	//set the state to initialized
	initialized = TRUE;

	return DRV_SUCCESS;
}


//Function to Load the driver.
DWORD TDriver::LoadDriver(LPCTSTR name, LPCTSTR path, LPCTSTR dosName, BOOL start)
{
	//first initialized it
	DWORD retCode = InitDriver(name, path, dosName);

	//then load
	if(retCode == DRV_SUCCESS)
		retCode = LoadDriver(start);

	return retCode;
}

//Function to load the driver
DWORD TDriver::LoadDriver(LPCTSTR path, BOOL start)
{
	//first initialized it
	DWORD retCode = InitDriver(path);

	//then load
	if(retCode == DRV_SUCCESS)
		retCode = LoadDriver(start);

	return retCode;
}


//Function to Load the driver
DWORD TDriver::LoadDriver(BOOL start)
{
	//if the driver is already started, i havent to do nothing
	if(loaded)
		return DRV_SUCCESS;

	if(!initialized)
		return DRV_ERROR_NO_INITIALIZED;

	//Open Service manager to create the new "service"
	SC_HANDLE SCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	DWORD retCode = DRV_SUCCESS;
	
	if (SCManager == NULL) 
		return DRV_ERROR_SCM;

    

    //Create the driver "service"
    SC_HANDLE  SCService = CreateService(SCManager,			  // SCManager database
									     driverName,            // nombre del servicio
							    		 driverName,            // nombre a mostrar
										 SERVICE_ALL_ACCESS,    // acceso total
										 SERVICE_KERNEL_DRIVER, // driver del kernel
										 SERVICE_DEMAND_START,  // comienzo bajo demanda
										 SERVICE_ERROR_NORMAL,  // control de errores normal
										 driverPath,	          // path del driver
										 NULL,                  // no pertenece a un grupo
										 NULL,                  // sin tag
										 NULL,                  // sin dependencias
										 NULL,                  // cuenta local del sistema
										 NULL                   // sin password
										 );
    
	//if i cant create, first i check if the driver already was loaded.
	if (SCService == NULL) 
	{
		SCService = OpenService(SCManager, driverName, SERVICE_ALL_ACCESS);
		
		if (SCService == NULL) 
			retCode = DRV_ERROR_SERVICE;
	}

    CloseServiceHandle(SCService);
	SCService=NULL;

	CloseServiceHandle(SCManager);
	SCManager = NULL;

	//if all ok, update the state and start if necessary
	if(retCode == DRV_SUCCESS)
	{
		loaded = TRUE;

		if(start)
			retCode = StartDriver();
	}

	return retCode;
}


//Function to Unload a driver
DWORD TDriver::UnloadDriver(BOOL forceClearData)
{
	DWORD retCode = DRV_SUCCESS;

	//if the driver is started, first i will stop it
	if (started)
	{
		if ((retCode = StopDriver()) == DRV_SUCCESS) 
		{
			//i only remove it, if it is mark to be removable
			if(removable)
			{
				//open service and delete it
				SC_HANDLE SCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
				
				if (SCManager == NULL) 
					return DRV_ERROR_SCM;

				SC_HANDLE SCService = OpenService(SCManager, driverName, SERVICE_ALL_ACCESS);
				
				if (SCService != NULL)
				{
					if(!DeleteService(SCService))
						retCode = DRV_ERROR_REMOVING;
					else
						retCode = DRV_SUCCESS;
				}

				else
					retCode = DRV_ERROR_SERVICE;

				CloseServiceHandle(SCService);
				SCService = NULL;

				CloseServiceHandle(SCManager);
				SCManager = NULL;

				//if all ok, update the state
				if(retCode == DRV_SUCCESS)
					loaded = FALSE;
			}
		}
	}

	//if the driver is initialized...
	if(initialized) 
	{
		//if there was some problem but i mark foreceClear, i will remove the data
		if(retCode != DRV_SUCCESS && forceClearData == FALSE)
			return retCode;
		
		//update the state
		initialized = FALSE;
				
		//free memory
		if(driverPath != NULL)
		{
			free(driverPath);
			driverPath = NULL;
		}


		if(driverDosName != NULL)
		{
			free(driverDosName);
			driverDosName = NULL;
		}

		if(driverName != NULL)
		{
			free(driverName);
			driverName = NULL;
		}

	}

	return retCode;
}



//Function to start the driver "service"
DWORD TDriver::StartDriver(void)
{
	//if already started, all ok
	if(started)
		return DRV_SUCCESS;

	//open the service manager and the service and change driver state
	SC_HANDLE SCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	DWORD retCode;
	
	if (SCManager == NULL) 
		return DRV_ERROR_SCM;

    SC_HANDLE SCService = OpenService(SCManager,
		                              driverName,
				                      SERVICE_ALL_ACCESS);
    
	if (SCService == NULL) 
        return DRV_ERROR_SERVICE;

    
    if (!StartService( SCService, 0, NULL)) 
	{
		//if the driver was started before i try to do it,
		//i will not remove, because it was created by other application
        if (GetLastError() == ERROR_SERVICE_ALREADY_RUNNING) 
		{
			removable = FALSE;

			retCode = DRV_SUCCESS;
		}

		else
			retCode = DRV_ERROR_STARTING;
    }

	else
		retCode = DRV_SUCCESS;

  
    CloseServiceHandle(SCService);
	SCService = NULL;

	CloseServiceHandle(SCManager);
	SCManager = NULL;

	//update the state and open device
	if(retCode == DRV_SUCCESS)
	{
		started = TRUE;

		retCode = OpenDevice();
	}

    return retCode;
}



//Function to stop driver "service"
DWORD TDriver::StopDriver(void)
{
	//if already stopped, all ok
	if(!started)
		return DRV_SUCCESS;

	//open the service manager and the service and change driver state
	SC_HANDLE SCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	DWORD retCode;
	
	if (SCManager == NULL) 
		return DRV_ERROR_SCM;

   
    SERVICE_STATUS  status;

    SC_HANDLE SCService = OpenService(SCManager, driverName, SERVICE_ALL_ACCESS);
    
	if (SCService != NULL)
	{
		//close the driver handle too
		CloseHandle(driverHandle); 
		driverHandle = NULL; 

		if(!ControlService(SCService, SERVICE_CONTROL_STOP, &status))
			retCode = DRV_ERROR_STOPPING;

		else
			retCode = DRV_SUCCESS;
	}

	else
		retCode = DRV_ERROR_SERVICE;
    CloseServiceHandle(SCService);
	SCService = NULL;

	CloseServiceHandle(SCManager);
	SCManager = NULL;

	if(retCode == DRV_SUCCESS)
		started = FALSE;
    return retCode;
}


//Funtion to open a driver handle
DWORD TDriver::OpenDevice(void)
{
	//if i already have a handle, first close it
	if (driverHandle != NULL) 
		CloseHandle(driverHandle);

    driverHandle = CreateFile(driverDosName,
							  GENERIC_READ | GENERIC_WRITE,
							  0,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);


    if(driverHandle == INVALID_HANDLE_VALUE)
		return DRV_ERROR_INVALID_HANDLE;
	
	return DRV_SUCCESS;
}


//Return the driverHandle obtained
HANDLE TDriver::GetDriverHandle(void)
{
	return driverHandle;
}


//Funtion to send data to the driver
DWORD TDriver::WriteIo(DWORD code, PVOID buffer, DWORD count)
{
	if(driverHandle == NULL)
		return DRV_ERROR_INVALID_HANDLE;

	DWORD bytesReturned;

	BOOL returnCode = DeviceIoControl(driverHandle,
								      code,
								      buffer,
								      count,
								      NULL,
								      0,
								      &bytesReturned,
								      NULL);

	if(!returnCode)
		return DRV_ERROR_IO;

	return DRV_SUCCESS;
}


//Functions to read data from the driver
DWORD TDriver::ReadIo(DWORD code, PVOID buffer, DWORD count)
{
	if(driverHandle == NULL)
		return DRV_ERROR_INVALID_HANDLE;

	DWORD bytesReturned;
	BOOL retCode = DeviceIoControl(driverHandle,
								   code,
								   NULL,
								   0,
								   buffer,
								   count,
								   &bytesReturned,
								   NULL);

	if(!retCode)
		return DRV_ERROR_IO;

	return bytesReturned;
}


//Function to do IO operation with the driver, read or write or both
DWORD TDriver::RawIo(DWORD code, PVOID inBuffer, DWORD inCount, PVOID outBuffer, DWORD outCount)
{
	if(driverHandle == NULL)
		return DRV_ERROR_INVALID_HANDLE;

	DWORD bytesReturned;
	BOOL retCode = DeviceIoControl(driverHandle,
								   code,
								   inBuffer,
								   inCount,
								   outBuffer,
								   outCount,
								   &bytesReturned,
								   NULL);

	if(!retCode)
		return DRV_ERROR_IO;

	return bytesReturned;
}