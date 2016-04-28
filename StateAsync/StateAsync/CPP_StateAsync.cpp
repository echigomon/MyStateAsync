#include "pch.h"
#include "StateAsync.h"

using namespace StateAsync;
using namespace Platform;

CPP_StateAsync::CPP_StateAsync()
{	// コンストラクタ（Job No. クリア）
	_state = EventCode::Notify;
	_job = 0;
}
CPP_StateAsync::CPP_StateAsync(int32 _value)
{	// コンストラクタ(Job No. 設定)
	_state = EventCode::Notify;
	_job = _value;
}
CPP_StateAsync::~CPP_StateAsync()
{	// ディストラクタ
}
EventCode CPP_StateAsync::State::get()
{
	return(_state);
}
void CPP_StateAsync::State::set(EventCode _value)
{
	_state = _value;
}
int32 CPP_StateAsync::Job::get()
{
	return(_job);
}
void CPP_StateAsync::Job::set(int32 _value)
{
	_job = _value;
}

void CPP_StateAsync::ClearAsync()
{
	State = EventCode::Notify;
}
void CPP_StateAsync::StepAsync()
{
	switch (State)
	{
		case EventCode::Notify:
			State = EventCode::Create;      // [0]->[1]
			break;
		case EventCode::Create:
			State = EventCode::Start;       // [1]->[2]
			break;
		case EventCode::Start:
			State = EventCode::Resume;      // [2]->[3]
			break;
		case EventCode::Resume:
			State = EventCode::Run;         // [3]->[4]
			break;
		case EventCode::Run:
			State = EventCode::Pause;       // [4]->[5]
			break;
		case EventCode::Pause:
			State = EventCode::Stop;        // [5]->[6]
			break;
		case EventCode::Stop:
			State = EventCode::Destroy;     // [6]->[7]
			break;
		case EventCode::Destroy:
			State = EventCode::End;         // [7]->[8]
			break;
		case EventCode::End:
			State = EventCode::Notify;      // [8]->[0]
			break;
		default:
			break;
	}
}

void CPP_StateAsync::StepAsync(EventCode _value)
{
	if (_value == EventCode::Create)
	{   // On Create
		if (State == EventCode::Notify)
		{   // [0]->[1]
			State = _value;
		}
		if (State == EventCode::Pause)
		{   // [5]->[1]
			State = _value;
		}
		if (State == EventCode::Stop)
		{   // [6]->[1]
			State = _value;
		}
	}
	if (_value == EventCode::Start)
	{   // On Start
		if (State == EventCode::Create)
		{   // [1]->[2]
			State = _value;
		}
		if (State == EventCode::Resume)
		{   // [3]->[2]
			State = _value;
		}
	}
	if (_value == EventCode::Resume)
	{   // On Resume
		if (State == EventCode::Start)
		{   // [2]->[3]
			State = _value;
		}
		if (State == EventCode::Pause)
		{   // [5]->[3]
			State = _value;
		}
		if (State == EventCode::Stop)
		{   // [6]->[3]
			State = _value;
		}
	}
	if ((_value == EventCode::Run) && (State == EventCode::Resume))
	{   // [3]->[4]
		State = _value;
	}
	if ((_value == EventCode::Pause) && (State == EventCode::Run))
	{   // [4]->[5]
		State = _value;
	}
	if ((_value == EventCode::Stop) && (State == EventCode::Pause))
	{   // [5]->[6]
		State = _value;
	}
	if ((_value == EventCode::Destroy) && (State == EventCode::Stop))
	{   // [6]->[7]
		State = _value;
	}
	if ((_value == EventCode::End) && (State == EventCode::Destroy))
	{   // [7]->[8]
		State = _value;
	}
	if ((_value == EventCode::Notify) && (State == EventCode::End))
	{   // [8]->[0]
		State = _value;
	}
}
