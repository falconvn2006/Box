#pragma once

namespace Box
{
	class TimeStep
	{
	public:
		TimeStep(float time)
			: m_Time(time)
		{
		}

		operator float() const { return GetSeconds(); }

		float GetSeconds() const { return m_Time; }
		float GetMiliSeconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}