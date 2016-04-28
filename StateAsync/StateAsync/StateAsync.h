#pragma once

namespace StateAsync
{

	public enum class EventCode
	{   // 状態情報
		Notify = 0,    // 0 : Notify
		Create,         // 1 : Create
		Start,          // 2 : Start
		Resume,         // 3 : Resume
		Run,            // 4 : Run
		Pause,          // 5 : Pause
		Stop,           // 6 : Stop
		Destroy,        // 7 : Destroy
		End             // 8 : End
	};

	public ref class CPP_StateAsync sealed
    {
    public:
		property EventCode State
		{	// 状態情報
			EventCode get();
			void set(EventCode _value);
		}
		property int32 Job
		{	// 処理情報
			int32 get();
			void set(int32 _value);
		}
		CPP_StateAsync();			// コンストラクタ
		CPP_StateAsync(int32 _value);
		void ClearAsync();
		void StepAsync();
		void StepAsync(EventCode _value);
	private:
		EventCode _state;			// 状態情報管理
		int32 _job;					// 処理情報管理

		~CPP_StateAsync();			// ディストラクタ
    };
}
