/*****************************************************************************
*                                                                            *
*  PrimeSense Sensor 5.x Alpha                                               *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of PrimeSense Sensor                                    *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#ifndef _XN_DEVICE_H_
#define _XN_DEVICE_H_

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <XnPlatform.h>
#include <XnStatus.h>
#include <XnDDK.h>
#include <XnStreamData.h>
#include <XnStreamDataSet.h>
#include <XnGeneralBuffer.h>
#include <XnStreamParams.h>
#include <XnPropertySet.h>
#include <XnTypes.h>

// General Defines
#define XN_DEVICE_READ_FRAME_TIMEOUT 2000

/** The basic definition of a Xiron device */ 
typedef struct XnDeviceDefinition
{
	/** The device unique name. */ 
	const XnChar*	cpName;

	/** A short description for the device. */ 
	const XnChar*	cpDescription;

	/** The device major version. */ 
	XnUInt8		nMajorVersion; 

	/** The device minor version. */ 
	XnUInt8		nMinorVersion;

	/** The compatible Xiron major version. */ 
	XnUInt8		nXironVersion;
} XnDeviceDefinition;

/** The Xiron device mode enumerator type. */ 
typedef enum {
	/** Read only mode. */ 
	XN_DEVICE_MODE_READ = 0,
	/** Write only mode. */ 
	XN_DEVICE_MODE_WRITE
} XnDeviceMode;

/** The Xiron device sharing mode. */
typedef enum {
	/* Device is exclusive for opening process. */
	XN_DEVICE_EXCLUSIVE = 0,
	/* Device is shared and can be opened by other processes. */
	XN_DEVICE_SHARED = 1
} XnDeviceSharingMode;

typedef XnChar XnConnectionString[XN_DEVICE_MAX_STRING_LENGTH];

/** This structure defines the Xiron device configuration (when opening a new device). */ 
typedef struct XnDeviceConfig
{
	/** The device I/O mode (read or write). */ 
	XnDeviceMode DeviceMode;
	/** The connection string (depending on the device this could mean: file name, IP, sensor serial, etc...). */ 
	const XnChar* cpConnectionString;
	/** Optional. A set of initial values to be used. */
	const XnPropertySet* pInitialValues;
	/** The device sharing mode. */
	XnDeviceSharingMode SharingMode;
} XnDeviceConfig;

typedef void* XnDeviceHandle;

typedef enum XnStreamsChangeEventType
{
	XN_DEVICE_STREAM_ADDED,
	XN_DEVICE_STREAM_DELETED,
} XnStreamsChangeEventType;

typedef struct XnStreamCollectionChangedEventArgs
{
	XnDeviceHandle deviceHandle; 
	const XnChar* strStreamName; 
	XnStreamsChangeEventType eventType;
} XnStreamCollectionChangedEventArgs;

typedef struct XnNewStreamDataEventArgs
{
	XnDeviceHandle deviceHandle;
	const XnChar* strStreamName;
} XnNewStreamDataEventArgs;

typedef void (XN_CALLBACK_TYPE* XnDeviceOnStreamsChangedEventHandler)(const XnStreamCollectionChangedEventArgs& args, void* pCookie);
typedef void (XN_CALLBACK_TYPE* XnDeviceOnPropertyChangedEventHandler)(XnDeviceHandle pDeviceHandle, const XnChar* ModuleName, const XnChar* PropertyName, void* pCookie);
typedef void (XN_CALLBACK_TYPE* XnDeviceOnNewStreamDataEventHandler)(const XnNewStreamDataEventArgs& args, void* pCookie);

//---------------------------------------------------------------------------
// Exported Functions Declaration. Every Device Must Implement Them All!
//---------------------------------------------------------------------------

// Function prototypes names
#define XN_DEVICE_PROTO_VAL(x,y) x ## y
#define XN_DEVICE_PROTO_APPEND(x,y) XN_DEVICE_PROTO_VAL(x,y)

#ifndef XN_DEVICE_EXPORT_PREFIX
	#define XN_DEVICE_EXPORT_PREFIX XnDevice
#endif

#define XN_DEVICE_PROTO_NAME(name)	XN_DEVICE_PROTO_APPEND(XN_DEVICE_EXPORT_PREFIX, name)
#define XN_DEVICE_INTERFACE_FUNCTION(name, sig) XN_DEVICE_API XnStatus XN_DEVICE_PROTO_NAME(name) sig;
#include "XnDeviceProto.inl"
#undef XN_DEVICE_INTERFACE_FUNCTION

#endif //_XN_DEVICE_H_