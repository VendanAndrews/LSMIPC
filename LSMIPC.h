#pragma once
#include <LSModule.h>
#include <windows.h>


class LSMIPC :
	public LSModuleInterface
{
public:
	LSMIPC(void);
	~LSMIPC(void);

	virtual bool Initialize(LSInterface *p_LSInterface);
	virtual void Shutdown();

	void RegisterCommands();
	void RegisterAliases();
	void RegisterDataTypes();
	void RegisterTopLevelObjects();
	void RegisterTriggers();
	void RegisterEvents(); // Events should NOT get unregistered

	void UnRegisterCommands();
	void UnRegisterAliases();
	void UnRegisterDataTypes();
	void UnRegisterTopLevelObjects();
	void UnRegisterTriggers();

};

extern LSInterface *pLSInterface;

extern LSMIPC *pModule;
#define printf pLSInterface->Printf

#define EzCheckTriggers(Text) IS_CheckTriggers(pExtension,pLSInterface,hTriggerService,Text)

extern LSTypeDefinition *pStringType;
extern LSTypeDefinition *pIntType;
extern LSTypeDefinition *pUintType;
extern LSTypeDefinition *pBoolType;
extern LSTypeDefinition *pFloatType;
extern LSTypeDefinition *pTimeType;
extern LSTypeDefinition *pByteType;
extern LSTypeDefinition *pIntPtrType;
extern LSTypeDefinition *pBoolPtrType;
extern LSTypeDefinition *pFloatPtrType;
extern LSTypeDefinition *pBytePtrType;
extern LSTypeDefinition *pIndexType;
extern LSTypeDefinition *pQueueType;
extern LSTypeDefinition *pSetType;
extern LSTypeDefinition *pCollectionType;
extern LSTypeDefinition *pStackType;
extern LSTypeDefinition *pIteratorType;

extern char IPC_Version[];

void IPCIndexEvent(int argc, char** argv, PLSOBJECT Object);
void IPCQueueEvent(int argc, char** argv, PLSOBJECT Object);
void IPCSetEvent(int argc, char** argv, PLSOBJECT Object);
void IPCCollectionEvent(int argc, char** argv, PLSOBJECT Object);

#include "Commands.h"
#include "DataTypes.h"
#include "TopLevelObjects.h"
#include "Events.h"
