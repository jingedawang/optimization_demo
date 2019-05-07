#include "time_recorder.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "glog/logging.h"

TimeRecorder::TimeRecorder(std::string title) : title_(title) {
}

TimeRecorder::~TimeRecorder() {
}

void TimeRecorder::start() {

    for (size_t i = 1; i < names_.size(); i++) {
        accumulated_times_[names_[i]].first++;
        accumulated_times_[names_[i]].second += std::chrono::duration_cast<std::chrono::duration<double> >(
                time_points_[i] - time_points_[i - 1]).count();
    }

    names_.clear();
    time_points_.clear();
    addTimePoint("start_time");
}

void TimeRecorder::addTimePoint(std::string name) {
    std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();
    time_points_.push_back(time_point);
    names_.push_back(name);
}

void TimeRecorder::print() {
    std::vector<std::string> names(++names_.cbegin(), names_.cend());
    std::vector<double> time_intervals;
    time_intervals.reserve(names.size());
    for (size_t i = 1; i < names_.size(); i++) {
        time_intervals.push_back(std::chrono::duration_cast<std::chrono::duration<double> >(
                time_points_[i] - time_points_[i - 1]).count());
    }
    print(title_, names, time_intervals);
}

void TimeRecorder::printAverageTimes() {
    std::vector<std::string> names(++names_.cbegin(), names_.cend());
    std::vector<double> time_intervals;
    time_intervals.reserve(names.size());
    for (size_t i = 0; i < names.size(); i++) {
        time_intervals.push_back(accumulated_times_[names[i]].second / accumulated_times_[names[i]].first);
    }
    print(title_ + " Average", names, time_intervals);
}

void TimeRecorder::print(const std::string &title, const std::vector<std::string> &names,
                         const std::vector<double> &time_intervals) {

    std::stringstream ss;

    ss << std::endl;
    ss.setf(std::ios::left);
    ss << "---";

    for (int i = 0; i < ((int) (names_.size() * 13 - title.size())) / 2; i++) {
        ss << "-";
    }
    ss << title;
    for (int i = 0; i < ((int) (names_.size() * 13 - title.size())) / 2; i++) {
        ss << "-";
    }
    ss << std::endl << "-- ";
    for (size_t i = 0; i < names.size(); i++) {
        ss.width(13);
        ss << names[i];
    }
    ss.width(13);
    ss << "Total" << std::endl << "-- ";
    for (size_t i = 0; i < time_intervals.size(); i++) {
        ss.width(13);
        ss << time_intervals[i];
    }
    ss.width(13);
    ss << std::accumulate(time_intervals.cbegin(), time_intervals.cend(), 0.0);
    ss << std::endl << "---";
    for (int i = 0; i < static_cast<int>(names_.size()) * 13; i++) {
        ss << "-";
    }
    ss << std::endl;

    LOG(INFO) << ss.str();
}