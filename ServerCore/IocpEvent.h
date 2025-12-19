#pragma once

class Session;

enum class EventType : uint8
{
	Connect,
	Disconnect,
	Accept,
	//PreRecv,
	Recv,
	Send
};

#pragma region IocpEvent

class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void		Init();

public:
	EventType		eventType;
	IocpObjectRef	owner;
};

#pragma endregion

#pragma region ConnectEvent

class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(EventType::Connect) { }
};

#pragma endregion

#pragma region DisconnectEvent

class DisconnectEvent : public IocpEvent
{
public:
	DisconnectEvent() : IocpEvent(EventType::Disconnect) { }
};

#pragma endregion

#pragma region AcceptEvent

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::Accept) { }

public:
	SessionRef	session = nullptr;
};


#pragma endregion

#pragma region RecvEvent

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::Recv) { }
};

#pragma endregion

#pragma region SendEvent

class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::Send) { }

	Vector<SendBufferRef> sendBuffers;
};

#pragma endregion