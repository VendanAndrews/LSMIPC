#include "LSMIPC.h"
#define DATATYPE(_class_,_variable_,_inherits_) class _class_ *_variable_=0
#include "DataTypeList.h"
#undef DATATYPE

/* Set up an easy way to access the object, given its 32-bit representation (e.g. a pointer to
   a class or structure) */
#undef pIndex
#define pIndex ((IPCIndex*)ObjectData.Ptr)
#undef pQueue
#define pQueue ((IPCQueue*)ObjectData.Ptr)
#undef pSet
#define pSet ((IPCSet*)ObjectData.Ptr)
#undef pCollection
#define pCollection ((IPCCollection*)ObjectData.Ptr)
#undef pStack
#define pStack ((IPCStack*)ObjectData.Ptr)

#pragma region IndexList

struct IndexList{
	char name[255];
	LSIndex* Index;
	IndexList* next;
};

IndexList indexHead;
IndexList* indexTail = &indexHead;

LSIndex* FindIndex(char* name)
{
	IndexList* cur = &indexHead;
	while(cur = cur->next)
	{
		if(strcmp(name, cur->name) == 0)
		{
			return cur->Index;
		}
	}
	return 0;
}

void AddIndex(char* name, LSIndex* Index)
{
	indexTail->next = (IndexList*)calloc(1, sizeof(IndexList));
	indexTail = indexTail->next;
	strncpy(indexTail->name, name, 254);
	indexTail->Index = Index;
}

#pragma endregion

#pragma region QueueList

struct QueueList{
	char name[255];
	LSQueue* Queue;
	QueueList* next;
};

QueueList QueueHead;
QueueList* queueTail = &QueueHead;

LSQueue* FindQueue(char* name)
{
	QueueList* cur = &QueueHead;
	while(cur = cur->next)
	{
		if(strcmp(name, cur->name) == 0)
		{
			return cur->Queue;
		}
	}
	return 0;
}

void AddQueue(char* name, LSQueue* Queue)
{
	queueTail->next = (QueueList*)calloc(1, sizeof(QueueList));
	queueTail = queueTail->next;
	strncpy(queueTail->name, name, 254);
	queueTail->Queue = Queue;
}

#pragma endregion

#pragma region SetList

struct SetList{
	char name[255];
	LSSet* Set;
	SetList* next;
};

SetList SetHead;
SetList* setTail = &SetHead;

LSSet* FindSet(char* name)
{
	SetList* cur = &SetHead;
	while(cur = cur->next)
	{
		if(strcmp(name, cur->name) == 0)
		{
			return cur->Set;
		}
	}
	return 0;
}

void AddSet(char* name, LSSet* Set)
{
	setTail->next = (SetList*)calloc(1, sizeof(SetList));
	setTail = setTail->next;
	strncpy(setTail->name, name, 254);
	setTail->Set = Set;
}

#pragma endregion

#pragma region CollectionList

struct CollectionList{
	char name[255];
	LSObjectCollection* Collection;
	CollectionList* next;
};

CollectionList CollectionHead;
CollectionList* collectionTail = &CollectionHead;

LSObjectCollection* FindCollection(char* name)
{
	CollectionList* cur = &CollectionHead;
	while(cur = cur->next)
	{
		if(strcmp(name, cur->name) == 0)
		{
			return cur->Collection;
		}
	}
	return 0;
}

void AddCollection(char* name, LSObjectCollection* Collection)
{
	collectionTail->next = (CollectionList*)calloc(1, sizeof(CollectionList));
	collectionTail = collectionTail->next;
	strncpy(collectionTail->name, name, 254);
	collectionTail->Collection = Collection;
}

#pragma endregion

#pragma region StackList

struct StackList{
	char name[255];
	LSStack* Stack;
	StackList* next;
};

StackList StackHead;
StackList* StackTail = &StackHead;

LSStack* FindStack(char* name)
{
	StackList* cur = &StackHead;
	while(cur = cur->next)
	{
		if(strcmp(name, cur->name) == 0)
		{
			return cur->Stack;
		}
	}
	return 0;
}

void AddStack(char* name, LSStack* Stack)
{
	StackTail->next = (StackList*)calloc(1, sizeof(StackList));
	StackTail = StackTail->next;
	strncpy(StackTail->name, name, 254);
	StackTail->Stack = Stack;
}

#pragma endregion

void IndexRelay(char* name, char* type, char* subtype, char* method, int argc, char** argv)
{
	int totallength = 0;
	char* copier;
	int argpos = 0;
	char* origformat = "relay \"all other\" \"Event[IPCIndex]:Execute[%n%t%s%m%a]\"";
	char* format = origformat;

	char* command;
	char* writer;
	bool addcomma = false;

	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 't':
				copier = type;
				break;
			case 's':
				copier = subtype;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				totallength+=6;
				for(;*copier;copier++)
				{
					totallength++;
					if(*copier=='"')
						totallength+=3;
				}
			}
			copier = 0;
		}
		else
		{
			totallength++;
		}
	}
	




	command = (char*)malloc(totallength+1);
	writer = command;
	format = origformat;
	argpos = 0;
	addcomma = false;
	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 't':
				copier = type;
				break;
			case 's':
				copier = subtype;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				if(addcomma)
				{
					*writer++=',';
					*writer++=' ';
				}
				*writer++='\\';
				*writer++='"';
				for(;*copier;copier++)
				{
					if(*copier=='"')
					{
						*writer++ = '\\';
						*writer++ = '\\';
						*writer++ = '\\';
					}
					*writer++ = *copier;
				}
				*writer++='\\';
				*writer++='"';
				addcomma = true;
			}
			copier = 0;
		}
		else
		{
			*writer++ = *format;
		}
	}
	*writer = 0;
	printf("%s", command);
	pLSInterface->ExecuteCommand(command);
	free(command);
}

void QueueRelay(char* name, char* type, char* subtype, char* method, int argc, char** argv)
{
	int totallength = 0;
	char* copier;
	int argpos = 0;
	char* origformat = "relay \"all other\" \"Event[IPCQueue]:Execute[%n%t%s%m%a]\"";
	char* format = origformat;

	char* command;
	char* writer;
	bool addcomma = false;

	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 't':
				copier = type;
				break;
			case 's':
				copier = subtype;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				totallength+=6;
				for(;*copier;copier++)
				{
					totallength++;
					if(*copier=='"')
						totallength+=3;
				}
			}
			copier = 0;
		}
		else
		{
			totallength++;
		}
	}
	




	command = (char*)malloc(totallength+1);
	writer = command;
	format = origformat;
	argpos = 0;
	addcomma = false;
	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 't':
				copier = type;
				break;
			case 's':
				copier = subtype;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				if(addcomma)
				{
					*writer++=',';
					*writer++=' ';
				}
				*writer++='\\';
				*writer++='"';
				for(;*copier;copier++)
				{
					if(*copier=='"')
					{
						*writer++ = '\\';
						*writer++ = '\\';
						*writer++ = '\\';
					}
					*writer++ = *copier;
				}
				*writer++='\\';
				*writer++='"';
				addcomma = true;
			}
			copier = 0;
		}
		else
		{
			*writer++ = *format;
		}
	}
	*writer = 0;
	printf("%s", command);
	pLSInterface->ExecuteCommand(command);
	free(command);
}

void SetRelay(char* name, char* method, int argc, char** argv)
{
	int totallength = 0;
	char* copier;
	int argpos = 0;
	char* origformat = "relay \"all other\" \"Event[IPCSet]:Execute[%n%m%a]\"";
	char* format = origformat;

	char* command;
	char* writer;
	bool addcomma = false;

	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				totallength+=6;
				for(;*copier;copier++)
				{
					totallength++;
					if(*copier=='"')
						totallength+=3;
				}
			}
			copier = 0;
		}
		else
		{
			totallength++;
		}
	}
	




	command = (char*)malloc(totallength+1);
	writer = command;
	format = origformat;
	argpos = 0;
	addcomma = false;
	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				if(addcomma)
				{
					*writer++=',';
					*writer++=' ';
				}
				*writer++='\\';
				*writer++='"';
				for(;*copier;copier++)
				{
					if(*copier=='"')
					{
						*writer++ = '\\';
						*writer++ = '\\';
						*writer++ = '\\';
					}
					*writer++ = *copier;
				}
				*writer++='\\';
				*writer++='"';
				addcomma = true;
			}
			copier = 0;
		}
		else
		{
			*writer++ = *format;
		}
	}
	*writer = 0;
	printf("%s", command);
	pLSInterface->ExecuteCommand(command);
	free(command);
}

void CollectionRelay(char* name, char* type, char* subtype, char* method, int argc, char** argv)
{
	int totallength = 0;
	char* copier;
	int argpos = 0;
	char* origformat = "relay \"all other\" \"Event[IPCCollection]:Execute[%n%t%s%m%a]\"";
	char* format = origformat;

	char* command;
	char* writer;
	bool addcomma = false;

	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 't':
				copier = type;
				break;
			case 's':
				copier = subtype;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				totallength+=6;
				for(;*copier;copier++)
				{
					totallength++;
					if(*copier=='"')
						totallength+=3;
				}
			}
			copier = 0;
		}
		else
		{
			totallength++;
		}
	}
	




	command = (char*)malloc(totallength+1);
	writer = command;
	format = origformat;
	argpos = 0;
	addcomma = false;
	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 't':
				copier = type;
				break;
			case 's':
				copier = subtype;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				if(addcomma)
				{
					*writer++=',';
					*writer++=' ';
				}
				*writer++='\\';
				*writer++='"';
				for(;*copier;copier++)
				{
					if(*copier=='"')
					{
						*writer++ = '\\';
						*writer++ = '\\';
						*writer++ = '\\';
					}
					*writer++ = *copier;
				}
				*writer++='\\';
				*writer++='"';
				addcomma = true;
			}
			copier = 0;
		}
		else
		{
			*writer++ = *format;
		}
	}
	*writer = 0;
	printf("%s", command);
	pLSInterface->ExecuteCommand(command);
	free(command);
}

void StackRelay(char* name, char* type, char* subtype, char* method, int argc, char** argv)
{
	int totallength = 0;
	char* copier;
	int argpos = 0;
	char* origformat = "relay \"all other\" \"Event[IPCStack]:Execute[%n%t%s%m%a]\"";
	char* format = origformat;

	char* command;
	char* writer;
	bool addcomma = false;

	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 't':
				copier = type;
				break;
			case 's':
				copier = subtype;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				totallength+=6;
				for(;*copier;copier++)
				{
					totallength++;
					if(*copier=='"')
						totallength+=3;
				}
			}
			copier = 0;
		}
		else
		{
			totallength++;
		}
	}
	




	command = (char*)malloc(totallength+1);
	writer = command;
	format = origformat;
	argpos = 0;
	addcomma = false;
	for(;*format; format++)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
			case 'n':
				copier = name;
				break;
			case 't':
				copier = type;
				break;
			case 's':
				copier = subtype;
				break;
			case 'm':
				copier = method;
				break;
			case 'a':
				if(argpos < argc)
				{
					copier = argv[argpos];
					argpos++;
					format-=2;
				}
			}
			if(copier)
			{
				if(addcomma)
				{
					*writer++=',';
					*writer++=' ';
				}
				*writer++='\\';
				*writer++='"';
				for(;*copier;copier++)
				{
					if(*copier=='"')
					{
						*writer++ = '\\';
						*writer++ = '\\';
						*writer++ = '\\';
					}
					*writer++ = *copier;
				}
				*writer++='\\';
				*writer++='"';
				addcomma = true;
			}
			copier = 0;
		}
		else
		{
			*writer++ = *format;
		}
	}
	*writer = 0;
	printf("%s", command);
	pLSInterface->ExecuteCommand(command);
	free(command);
}

void IPCIndexEvent(int argc, char** argv, PLSOBJECT Object)
{
	char* Name = argv[0];
	LSTypeDefinition* Type = pLSInterface->FindLSType(argv[1]);
	char* SubType = argv[2];
	char* Method = argv[3];

	LSOBJECT indexobject;
	if((indexobject.Ptr = FindIndex(Name)) == 0)
	{
		indexobject.Ptr = new LSIndex(Type, SubType);
		AddIndex(Name, (LSIndex*)indexobject.Ptr);
	}
	pIndexType->GetMethodEx(indexobject.ObjectData, Method, argc-4, &argv[4]);
}

void IPCQueueEvent(int argc, char** argv, PLSOBJECT Object)
{
	char* Name = argv[0];
	LSTypeDefinition* Type = pLSInterface->FindLSType(argv[1]);
	char* SubType = argv[2];
	char* Method = argv[3];

	LSOBJECT queueobject;
	if((queueobject.Ptr = FindQueue(Name)) == 0)
	{
		queueobject.Ptr = new LSQueue(Type, SubType);
		AddQueue(Name, (LSQueue*)queueobject.Ptr);
	}
	pQueueType->GetMethodEx(queueobject.ObjectData, Method, argc-4, &argv[4]);
}

void IPCSetEvent(int argc, char** argv, PLSOBJECT Object)
{
	char* Name = argv[0];
	char* Method = argv[1];

	LSOBJECT setobject;
	if((setobject.Ptr = FindSet(Name)) == 0)
	{
		setobject.Ptr = new LSSet();
		AddSet(Name, (LSSet*)setobject.Ptr);
	}
	pSetType->GetMethodEx(setobject.ObjectData, Method, argc-2, &argv[2]);
}

void IPCCollectionEvent(int argc, char** argv, PLSOBJECT Object)
{
	char* Name = argv[0];
	LSTypeDefinition* Type = pLSInterface->FindLSType(argv[1]);
	char* SubType = argv[2];
	char* Method = argv[3];

	LSOBJECT collectionobject;
	if((collectionobject.Ptr = FindCollection(Name)) == 0)
	{
		collectionobject.Ptr = new LSObjectCollection(Type, SubType);
		AddCollection(Name, (LSObjectCollection*)collectionobject.Ptr);
	}
	pCollectionType->GetMethodEx(collectionobject.ObjectData, Method, argc-4, &argv[4]);
}

void IPCStackEvent(int argc, char** argv, PLSOBJECT Object)
{
	char* Name = argv[0];
	LSTypeDefinition* Type = pLSInterface->FindLSType(argv[1]);
	char* SubType = argv[2];
	char* Method = argv[3];

	LSOBJECT Stackobject;
	if((Stackobject.Ptr = FindStack(Name)) == 0)
	{
		Stackobject.Ptr = new LSStack(Type, SubType);
		AddStack(Name, (LSStack*)Stackobject.Ptr);
	}
	pStackType->GetMethodEx(Stackobject.ObjectData, Method, argc-4, &argv[4]);
}

#pragma region Index

bool IPCIndexType::GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object)
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMEMBER pMember: pMember is a pointer to the information on the member to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the member, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the member is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the member retrieval.
 *
 * [out] LSOBJECT &Object: Object is an object that is the result of the member retrieval operation.  An LSOBJECT
 *        is an LSOBJECTDATA, in addition to a separate Type value used to give the value context (in the first
 *        parameter, the context is already known to be the ipcfoo object type, so it is LSOBJECTDATA).
 *
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the member retrieval fails for any reason, return false.
 * If Object is a valid object and the member retrieval is successful, return true.
 *
 */

	/* Validate the pointer */
	if (!pIndex)
		return false;

	/* Perform the given member retrieval */
	switch(pMember->ID)
	{
	case Get:
		if (argc)
		{
			unsigned int N=atoi(argv[0]);
			PLSOBJECT item = pIndex->Index->GetItem(N);
			Object.Type = item->Type;
			Object.DWord = item->DWord;
			return true;
		}
		return false;
	}
	return false;
}

bool IPCIndexType::GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[])
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMETHOD pMethod: pMethod is a pointer to the information on the method to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the method, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the method is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the method retrieval.
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the method execution fails for any reason, OR the object
 * is destroyed during execution, return false.  Otherwise, return true (indicating the object still exists AND
 * the method execution succeeded).
 *
 */
	/* Validate the pointer */
	if (!pIndex)
		return false;

	/* Perform the given member retrieval */
	switch(pMethod->ID)
	{
	case Insert:
		pIndex->Index->AddItem(argc, argv);
		IndexRelay(pIndex->IPCName, pIndex->Type->GetName(), pIndex->SubType, "Insert", argc, argv);
		return true;
	case Remove:
		if(argc)
		{
			int N = atoi(argv[0]);
			pIndex->Index->DeleteItem(N);
			IndexRelay(pIndex->IPCName, pIndex->Type->GetName(), pIndex->SubType, "Remove", argc, argv);
		}
		return true;
	case Clear:
		pIndex->Index->Clear();
		IndexRelay(pIndex->IPCName, pIndex->Type->GetName(), pIndex->SubType, "Clear", argc, argv);
		return true;
	case Set:
		if (argc>1)
		{
			unsigned int N=atoi(argv[0]);
			
			return pIndex->Index->SetItem(N, argc-1, &argv[1]);
			IndexRelay(pIndex->IPCName, pIndex->Type->GetName(), pIndex->SubType, "Set", argc, argv);
		}
	case SetIPCName:
		if(argc==1)
		{
			LSIndex *newIndex;
			strncpy(pIndex->IPCName, argv[0], sizeof(pIndex->IPCName));
			if((newIndex=FindIndex(pIndex->IPCName))==0)
			{
				newIndex = new LSIndex(pIndex->Type, pIndex->SubType);
				AddIndex(pIndex->IPCName, newIndex);
			}
			pIndex->Index = newIndex;
			return true;
		}
		return false;
	case GetIterator:
		LSOBJECT iteratorobject;
		if(argc)
		{
			//printf("%s %s %d", argv[0], pIndex->IPCName, pIndex->Index->GetContainerUsed());
			if(pLSInterface->DataParse(argv[0], iteratorobject))
			{
				return InitializeIterator(pIndex->Index, 0, iteratorobject);
			}
		}
		return false;
	}
	return false;
}

/* Retrieve some object, an index of an object of this type, using the given arguments */
int IPCIndexType::GetIndex(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object)
{
	// Quick and dirty way to reroute index retrieval to the Cloud member
	return GetMemberEx(ObjectData,"Get",argc,argv,Object);
}

/* Reduce an object of this type to text */
bool IPCIndexType::ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen)
{
	strncpy(buf,pIndex->IPCName,buflen);
	buf[buflen-1]=0;
	return true;
}

/* 
 * Initialize a new variable of this type, potentially with an object sub-type.  In this case,
 * since our object type works on IPCFoo*, we instantiate a IPCFoo
 * structure.  If our object type should not support variables, we could simply return false.
*/
bool IPCIndexType::InitVariable(LSOBJECTDATA &ObjectData, const char *SubType)
{
	ObjectData.Ptr=new IPCIndex;
	if (SubType && SubType[0])
	{
		pIndex->Type = pLSInterface->FindLSTypeDefinition(SubType, pIndex->SubType, 512);
	}
	else
	{
		return false;
	}
	return true;
}

/* As the second stage of initializing a variable of this type, assign the given value(s).  This will
 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
bool IPCIndexType::FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[])
{
	GetMethodEx(ObjectData, "SetIPCName", argc, argv);
	return true;
}

/* Destroy a variable of this type */
void IPCIndexType::FreeVariable(LSOBJECTDATA &ObjectData)
{
	delete pIndex;
}

#pragma endregion

#pragma region Queue

bool IPCQueueType::GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object)
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMEMBER pMember: pMember is a pointer to the information on the member to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the member, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the member is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the member retrieval.
 *
 * [out] LSOBJECT &Object: Object is an object that is the result of the member retrieval operation.  An LSOBJECT
 *        is an LSOBJECTDATA, in addition to a separate Type value used to give the value context (in the first
 *        parameter, the context is already known to be the ipcfoo object type, so it is LSOBJECTDATA).
 *
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the member retrieval fails for any reason, return false.
 * If Object is a valid object and the member retrieval is successful, return true.
 *
 */

	/* Validate the pointer */
	if (!pQueue)
		return false;

	/* Perform the given member retrieval */
	switch(pMember->ID)
	{
	case Peek:
		if (argc)
		{
			unsigned int N=atoi(argv[0]);
			LSOBJECT item;
			pQueue->Queue->Peek(item);
			Object.Type = item.Type;
			Object.DWord = item.DWord;
			return true;
		}
		return false;
	}
	return false;
}

bool IPCQueueType::GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[])
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMETHOD pMethod: pMethod is a pointer to the information on the method to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the method, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the method is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the method retrieval.
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the method execution fails for any reason, OR the object
 * is destroyed during execution, return false.  Otherwise, return true (indicating the object still exists AND
 * the method execution succeeded).
 *
 */
	/* Validate the pointer */
	if (!pQueue)
		return false;

	/* Perform the given member retrieval */
	switch(pMethod->ID)
	{
	case Queue:
		pQueue->Queue->Queue(argc, argv);
		QueueRelay(pQueue->IPCName, pQueue->Type->GetName(), pQueue->SubType, "Queue", argc, argv);
		return true;
	case Dequeue:
		pQueue->Queue->Dequeue();
		QueueRelay(pQueue->IPCName, pQueue->Type->GetName(), pQueue->SubType, "Dequeue", argc, argv);
		return true;
	case Clear:
		pQueue->Queue->Clear();
		QueueRelay(pQueue->IPCName, pQueue->Type->GetName(), pQueue->SubType, "Clear", argc, argv);
		return true;
	case Set:
	case SetIPCName:
		if(argc)
		{
			LSQueue *newQueue;
			strncpy(pQueue->IPCName, argv[0], sizeof(pQueue->IPCName));
			if((newQueue=FindQueue(pQueue->IPCName))==0)
			{
				newQueue = new LSQueue(pQueue->Type, pQueue->SubType);
				AddQueue(pQueue->IPCName, newQueue);
			}
			pQueue->Queue = newQueue;
			return true;
		}
		return false;
	case GetIterator:
		LSOBJECT iteratorobject;
		if(argc)
		{
			//printf("%s %s %d", argv[0], pQueue->IPCName, pQueue->Queue->GetContainerUsed());
			if(pLSInterface->DataParse(argv[0], iteratorobject))
			{
				return InitializeIterator(pQueue->Queue, 0, iteratorobject);
			}
		}
		return false;
	}
	return false;
}

/* Retrieve some object, an Queue of an object of this type, using the given arguments */
int IPCQueueType::GetQueue(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object)
{
	return GetMemberEx(ObjectData,"Peek",argc,argv,Object);
}

/* Reduce an object of this type to text */
bool IPCQueueType::ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen)
{
	strncpy(buf,pQueue->IPCName,buflen);
	buf[buflen-1]=0;
	return true;
}

/* 
 * Initialize a new variable of this type, potentially with an object sub-type.  In this case,
 * since our object type works on IPCFoo*, we instantiate a IPCFoo
 * structure.  If our object type should not support variables, we could simply return false.
*/
bool IPCQueueType::InitVariable(LSOBJECTDATA &ObjectData, const char *SubType)
{
	ObjectData.Ptr=new IPCQueue;
	if (SubType && SubType[0])
	{
		pQueue->Type = pLSInterface->FindLSTypeDefinition(SubType, pQueue->SubType, 512);
	}
	else
	{
		return false;
	}
	return true;
}

/* As the second stage of initializing a variable of this type, assign the given value(s).  This will
 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
bool IPCQueueType::FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[])
{
	GetMethodEx(ObjectData, "SetIPCName", argc, argv);
	return true;
}

/* Destroy a variable of this type */
void IPCQueueType::FreeVariable(LSOBJECTDATA &ObjectData)
{
	delete pQueue;
}

#pragma endregion

#pragma region Set

bool IPCSetType::GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object)
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMEMBER pMember: pMember is a pointer to the information on the member to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the member, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the member is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the member retrieval.
 *
 * [out] LSOBJECT &Object: Object is an object that is the result of the member retrieval operation.  An LSOBJECT
 *        is an LSOBJECTDATA, in addition to a separate Type value used to give the value context (in the first
 *        parameter, the context is already known to be the ipcfoo object type, so it is LSOBJECTDATA).
 *
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the member retrieval fails for any reason, return false.
 * If Object is a valid object and the member retrieval is successful, return true.
 *
 */

	/* Validate the pointer */
	if (!pSet)
		return false;

	/* Perform the given member retrieval */
	switch(pMember->ID)
	{
	case Contains:
		if (argc)
		{
			Object.Type = pBoolType;
			Object.Int = pSet->Set->Contains(argv[0]);
			return true;
		}
		return false;
	}
	return false;
}

bool IPCSetType::GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[])
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMETHOD pMethod: pMethod is a pointer to the information on the method to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the method, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the method is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the method retrieval.
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the method execution fails for any reason, OR the object
 * is destroyed during execution, return false.  Otherwise, return true (indicating the object still exists AND
 * the method execution succeeded).
 *
 */
	/* Validate the pointer */
	if (!pSet)
		return false;

	/* Perform the given member retrieval */
	switch(pMethod->ID)
	{
	case Add:
		if(argc)
		{
			pSet->Set->AddItem(argv[0]);
			SetRelay(pSet->IPCName, "Add", argc, argv);
			return true;
		}
		return false;
	case Remove:
		if(argc)
		{
			pSet->Set->RemoveItem(argv[0]);
			SetRelay(pSet->IPCName, "Remove", argc, argv);
			return true;
		}
		return false;
	case Set:
	case SetIPCName:
		if(argc)
		{
			LSSet *newSet;
			strncpy(pSet->IPCName, argv[0], sizeof(pSet->IPCName));
			if((newSet=FindSet(pSet->IPCName))==0)
			{
				newSet = new LSSet();
				AddSet(pSet->IPCName, newSet);
			}
			pSet->Set = newSet;
			return true;
		}
		return false;
	case GetIterator:
		LSOBJECT iteratorobject;
		if(argc)
		{
			//printf("%s %s %d", argv[0], pSet->IPCName, pSet->Set->GetContainerUsed());
			if(pLSInterface->DataParse(argv[0], iteratorobject))
			{
				return InitializeIterator(pSet->Set, 0, iteratorobject);
			}
		}
		return false;
	}
	return false;
}

/* Retrieve some object, an Set of an object of this type, using the given arguments */
int IPCSetType::GetSet(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object)
{
	// Quick and dirty way to reroute Set retrieval to the Cloud member
	return GetMemberEx(ObjectData,"Contains",argc,argv,Object);
}

/* Reduce an object of this type to text */
bool IPCSetType::ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen)
{
	strncpy(buf,pSet->IPCName,buflen);
	buf[buflen-1]=0;
	return true;
}

/* 
 * Initialize a new variable of this type, potentially with an object sub-type.  In this case,
 * since our object type works on IPCFoo*, we instantiate a IPCFoo
 * structure.  If our object type should not support variables, we could simply return false.
*/
bool IPCSetType::InitVariable(LSOBJECTDATA &ObjectData, const char *SubType)
{
	ObjectData.Ptr=new IPCSet;
	return true;
}

/* As the second stage of initializing a variable of this type, assign the given value(s).  This will
 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
bool IPCSetType::FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[])
{
	GetMethodEx(ObjectData, "SetIPCName", argc, argv);
	return true;
}

/* Destroy a variable of this type */
void IPCSetType::FreeVariable(LSOBJECTDATA &ObjectData)
{
	delete pSet;
}

#pragma endregion

#pragma region Collection

bool IPCCollectionType::GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object)
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMEMBER pMember: pMember is a pointer to the information on the member to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the member, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the member is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the member retrieval.
 *
 * [out] LSOBJECT &Object: Object is an object that is the result of the member retrieval operation.  An LSOBJECT
 *        is an LSOBJECTDATA, in addition to a separate Type value used to give the value context (in the first
 *        parameter, the context is already known to be the ipcfoo object type, so it is LSOBJECTDATA).
 *
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the member retrieval fails for any reason, return false.
 * If Object is a valid object and the member retrieval is successful, return true.
 *
 */

	/* Validate the pointer */
	if (!pCollection)
		return false;

	/* Perform the given member retrieval */
	switch(pMember->ID)
	{
	case Element:
		if (argc)
		{
			LSOBJECT item;
			pCollection->Collection->GetItem(argv[0], item);
			Object.Type = item.Type;
			Object.DWord = item.DWord;
			return true;
		}
		return false;
	}
	return false;
}

bool IPCCollectionType::GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[])
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMETHOD pMethod: pMethod is a pointer to the information on the method to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the method, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the method is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the method retrieval.
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the method execution fails for any reason, OR the object
 * is destroyed during execution, return false.  Otherwise, return true (indicating the object still exists AND
 * the method execution succeeded).
 *
 */
	/* Validate the pointer */
	if (!pCollection)
		return false;

	/* Perform the given member retrieval */
	switch(pMethod->ID)
	{
	case Erase:
		if(argc)
		{
			pCollection->Collection->RemoveItem(argv[0]);
			CollectionRelay(pCollection->IPCName, pCollection->Type->GetName(), pCollection->SubType, "Erase", argc, argv);
			return true;
		}
		return false;
	case Clear:
		pCollection->Collection->Clear();
		CollectionRelay(pCollection->IPCName, pCollection->Type->GetName(), pCollection->SubType, "Clear", argc, argv);
		return true;
	case Set:
		if (argc>1)
		{			
			pCollection->Collection->SetItem(argv[0], argc-1, &argv[1]);
			CollectionRelay(pCollection->IPCName, pCollection->Type->GetName(), pCollection->SubType, "Set", argc, argv);
			return true;
		}
	case SetIPCName:
		if(argc==1)
		{
			LSObjectCollection *newCollection;
			strncpy(pCollection->IPCName, argv[0], sizeof(pCollection->IPCName));
			if((newCollection=FindCollection(pCollection->IPCName))==0)
			{
				newCollection = new LSObjectCollection(pCollection->Type, pCollection->SubType);
				AddCollection(pCollection->IPCName, newCollection);
			}
			pCollection->Collection = newCollection;
			return true;
		}
		return false;
	case GetIterator:
		LSOBJECT iteratorobject;
		if(argc)
		{
			//printf("%s %s %d", argv[0], pCollection->IPCName, pCollection->Collection->GetContainerUsed());
			if(pLSInterface->DataParse(argv[0], iteratorobject))
			{
				return InitializeIterator(pCollection->Collection, 0, iteratorobject);
			}
		}
		return false;
	}
	return false;
}

/* Retrieve some object, an Collection of an object of this type, using the given arguments */
int IPCCollectionType::GetCollection(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object)
{
	// Quick and dirty way to reroute Collection retrieval to the Cloud member
	return GetMemberEx(ObjectData,"Element",argc,argv,Object);
}

/* Reduce an object of this type to text */
bool IPCCollectionType::ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen)
{
	strncpy(buf,pCollection->IPCName,buflen);
	buf[buflen-1]=0;
	return true;
}

/* 
 * Initialize a new variable of this type, potentially with an object sub-type.  In this case,
 * since our object type works on IPCFoo*, we instantiate a IPCFoo
 * structure.  If our object type should not support variables, we could simply return false.
*/
bool IPCCollectionType::InitVariable(LSOBJECTDATA &ObjectData, const char *SubType)
{
	ObjectData.Ptr=new IPCCollection;
	if (SubType && SubType[0])
	{
		pCollection->Type = pLSInterface->FindLSTypeDefinition(SubType, pCollection->SubType, 512);
	}
	else
	{
		return false;
	}
	return true;
}

/* As the second stage of initializing a variable of this type, assign the given value(s).  This will
 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
bool IPCCollectionType::FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[])
{
	GetMethodEx(ObjectData, "SetIPCName", argc, argv);
	return true;
}

/* Destroy a variable of this type */
void IPCCollectionType::FreeVariable(LSOBJECTDATA &ObjectData)
{
	delete pCollection;
}

#pragma endregion

#pragma region Stack

bool IPCStackType::GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object)
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMEMBER pMember: pMember is a pointer to the information on the member to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the member, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the member is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the member retrieval.
 *
 * [out] LSOBJECT &Object: Object is an object that is the result of the member retrieval operation.  An LSOBJECT
 *        is an LSOBJECTDATA, in addition to a separate Type value used to give the value context (in the first
 *        parameter, the context is already known to be the ipcfoo object type, so it is LSOBJECTDATA).
 *
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the member retrieval fails for any reason, return false.
 * If Object is a valid object and the member retrieval is successful, return true.
 *
 */

	/* Validate the pointer */
	if (!pStack)
		return false;

	/* Perform the given member retrieval */
	switch(pMember->ID)
	{
	case Top:
		LSOBJECT item;
		pStack->Stack->Top(item);
		Object.Type = item.Type;
		Object.DWord = item.DWord;
		return true;
	}
	return false;
}

bool IPCStackType::GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[])
{
/*******************************************
 * Parameters
 *
 * [in] LSOBJECTDATA ObjectData: ObjectData is a 32-bit value that can be accessed in any number of different ways
 *        by way of union.  Most commonly, ObjectData.Ptr, ObjectData.DWord, or ObjectData.CharPtr are useful.  This
 *        value is the representation of some object of this object type.  "ipcfoo" works on IPCFoo*
 *        so ObjectData is a IPCFoo*
 *
 * [in] PLSTYPEMETHOD pMethod: pMethod is a pointer to the information on the method to be retrieved, including its
 *        Name and ID.  We use the ID in a switch statement in order to quickly process the method, since the Name
 *        has already been resolved by the LavishScript engine.
 *
 * [in] int argc, char *argv[]: argc and argv are *nearly* standard C console program parameters.  The difference here
 *        is that the name of the method is NOT given as the first argument (in contrast to LavishScript commands).
 *        Therefore, argc is 0 unless arguments are specifically given to the method retrieval.
 */

/*******************************************
 * Return Value
 *
 * The return value for this function is very simple.  If the method execution fails for any reason, OR the object
 * is destroyed during execution, return false.  Otherwise, return true (indicating the object still exists AND
 * the method execution succeeded).
 *
 */
	/* Validate the pointer */
	if (!pStack)
		return false;

	/* Perform the given member retrieval */
	switch(pMethod->ID)
	{
	case Push:
		pStack->Stack->Push(argc, argv);
		StackRelay(pStack->IPCName, pStack->Type->GetName(), pStack->SubType, "Stack", argc, argv);
		return true;
	case Pop:
		pStack->Stack->Pop();
		StackRelay(pStack->IPCName, pStack->Type->GetName(), pStack->SubType, "DeStack", argc, argv);
		return true;
	case Clear:
		pStack->Stack->Clear();
		StackRelay(pStack->IPCName, pStack->Type->GetName(), pStack->SubType, "Clear", argc, argv);
		return true;
	case Set:
	case SetIPCName:
		if(argc)
		{
			LSStack *newStack;
			strncpy(pStack->IPCName, argv[0], sizeof(pStack->IPCName));
			if((newStack=FindStack(pStack->IPCName))==0)
			{
				newStack = new LSStack(pStack->Type, pStack->SubType);
				AddStack(pStack->IPCName, newStack);
			}
			pStack->Stack = newStack;
			return true;
		}
		return false;
	case GetIterator:
		LSOBJECT iteratorobject;
		if(argc)
		{
			//printf("%s %s %d", argv[0], pStack->IPCName, pStack->Stack->GetContainerUsed());
			if(pLSInterface->DataParse(argv[0], iteratorobject))
			{
				return InitializeIterator(pStack->Stack, 0, iteratorobject);
			}
		}
		return false;
	}
	return false;
}

/* Retrieve some object, an Stack of an object of this type, using the given arguments */
int IPCStackType::GetStack(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object)
{
	return GetMemberEx(ObjectData,"Peek",argc,argv,Object);
}

/* Reduce an object of this type to text */
bool IPCStackType::ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen)
{
	strncpy(buf,pStack->IPCName,buflen);
	buf[buflen-1]=0;
	return true;
}

/* 
 * Initialize a new variable of this type, potentially with an object sub-type.  In this case,
 * since our object type works on IPCFoo*, we instantiate a IPCFoo
 * structure.  If our object type should not support variables, we could simply return false.
*/
bool IPCStackType::InitVariable(LSOBJECTDATA &ObjectData, const char *SubType)
{
	ObjectData.Ptr=new IPCStack;
	if (SubType && SubType[0])
	{
		pStack->Type = pLSInterface->FindLSTypeDefinition(SubType, pStack->SubType, 512);
	}
	else
	{
		return false;
	}
	return true;
}

/* As the second stage of initializing a variable of this type, assign the given value(s).  This will
 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
bool IPCStackType::FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[])
{
	GetMethodEx(ObjectData, "SetIPCName", argc, argv);
	return true;
}

/* Destroy a variable of this type */
void IPCStackType::FreeVariable(LSOBJECTDATA &ObjectData)
{
	delete pStack;
}

#pragma endregion
