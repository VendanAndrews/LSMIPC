#ifndef EVENT
#define EVENT_SELF
#define EVENT(_eventname_,_variable_) extern unsigned int _variable_
#endif
// ----------------------------------------------------
// Events

/*
 *  Our sample event is called IPCEvent.  There is no restriction on naming schemes, but it may
 *  be easier to describe events to other developers if your event names follow the rules of function naming.
 * 
 *  The event will be executed later with our Event_IPC variable.  This will be populated in the
 *  default initialize sequence with an ID number to this registered event.
 *
 *  Our event will use one parameter, and it will be an integer, so we can describe the event as in the
 *  comment below, which would indicate that our event named IPCEvent has one parameter that
 *  we call Value, and it is an int type.
 */

EVENT("IPCIndex", pIPCIndexEvent);









// ----------------------------------------------------
#ifdef EVENT_SELF
#undef EVENT_SELF
#undef EVENT
#endif