#pragma once
namespace Arcanoid
{
	class IDelayedAction
	{
	protected:
		bool isTimerStarted = false;
		float currentTime;
		float destroyTime;

		virtual void UpdateTimer(float deltaTime)
		{
			if (!isTimerStarted)
			{
				return;
			}
			currentTime -= deltaTime;
			EachTickAction(deltaTime);
			if (currentTime <= 0)
			{
				isTimerStarted = false;
			}
		}

		virtual void EachTickAction(float deltaTime) = 0;
	public:
		void StartTimer(float destroyTime) 
		{
			this->destroyTime = destroyTime;
			this->currentTime = destroyTime;
			this->isTimerStarted = true;
		}
	};
}