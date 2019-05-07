#ifndef TIME_RECORDER_H
#define TIME_RECORDER_H

#include <string>
#include <vector>
#include <map>
#include <chrono>

class TimeRecorder {
public:
	TimeRecorder(std::string title = "Time used");

	virtual ~TimeRecorder();

	void start();

	void addTimePoint(std::string name);

	void print();

	void printAverageTimes();

private:

	void print(const std::string &title, const std::vector<std::string> &names,
			   const std::vector<double> &time_intervals);

	std::string title_;
	std::vector<std::chrono::steady_clock::time_point> time_points_;
	std::vector<std::string> names_;
	std::map<std::string, std::pair<size_t, double>> accumulated_times_;

};

#endif // TIME_RECORDER_H