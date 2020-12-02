# ifndef STOPWATCH11_H
#	define STOPWATCH11_H
#	include <chrono>

	using namespace std::chrono;
	class TimerBaseChrono {
	public:
        // tick type
        using tick_t = system_clock::duration::rep;

		//	clears the timer
		TimerBaseChrono() : m_start(system_clock::time_point::min()) { }

		//  clears the timer
		void Clear() { 
			m_start = system_clock::time_point::min(); 
		}

		//	returns true if the timer is running
		bool IsStarted() const {
			return (m_start != system_clock::time_point::min());
		}

		//	start the timer
		void Start()            { m_start = std::chrono::system_clock::now(); }

        // get elapsed time in ticks
        tick_t GetTicks() {
            if (IsStarted()) {
                auto now = system_clock::now();
                auto dt  = (now - m_start);
                return dt.count();
            }
            return 0;
        }

		//	get the number of milliseconds since the timer was started
		unsigned long GetMs() {
			if (IsStarted()) {
				system_clock::duration diff;
				diff = system_clock::now() - m_start;
				return (unsigned)(duration_cast<milliseconds>(diff).count());
			}
			return 0;
		}
        static unsigned GetMs(tick_t dt) {
            return (unsigned)(duration_cast<milliseconds>(system_clock::duration(dt)).count());
        }
	private:
		std::chrono::system_clock::time_point m_start;
	}; 
#   include "stopwatch.h"
	typedef basic_stopwatch<TimerBaseChrono> Stopwatch;
# endif