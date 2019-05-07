#include <iostream>
#include <vector>
#include <chrono>

#include "glog/logging.h"

#include "time_recorder.h"

using namespace std;

/* Trival implementation */
long combine_trival(const vector<int>& v) {
    long sum = 0;
    for (size_t i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum;
}

/* A bad trival implementation */
void combine_trival_bad(const vector<int>& v, long& result) {
    for (size_t i = 0; i < v.size(); i++) {
        result += v[i];
    }
}

/* Move call to v.size() out of loop */
long combine_outofloop(const vector<int>& v) {
    long sum = 0;
    size_t size = v.size();
    for (size_t i = 0; i < size; i++) {
        sum += v[i];
    }
    return sum;
}

/* Direct access to vector data */
long combine_direct_access(const vector<int>& v) {
    long sum = 0;
    const int* end = v.data() + v.size();
    for (const int* i = v.data(); i < end; i++) {
        sum += *i;
    }
    return sum;
}

/* Unroll loop by 2 */
long combine_unroll_2(const vector<int>& v) {
    long sum = 0;
    const int* i;
    const int* end = v.data() + v.size();
    for (i = v.data(); i < end; i += 2) {
        sum = sum + *i + *(i+1);
    }
    for (; i < end; i++) {
        sum += *i;
    }
    return sum;
}

/* Unroll loop by 3 */
long combine_unroll_3(const vector<int>& v) {
    long sum = 0;
    const int* i;
    const int* end = v.data() + v.size();
    for (i = v.data(); i < end; i += 3) {
        sum = sum + *i + *(i + 1) + *(i + 2);
    }
    for (; i < end; i++) {
        sum += *i;
    }
    return sum;
}

/* Unroll loop by 4 */
long combine_unroll_4(const vector<int>& v) {
    long sum = 0;
    const int* i;
    const int* end = v.data() + v.size();
    for (i = v.data(); i < end; i += 4) {
        sum = sum + *i + *(i + 1) + *(i + 2) + *(i + 3);
    }
    for (; i < end; i++) {
        sum += *i;
    }
    return sum;
}

/* Unroll by compiler */
__attribute__((optimize("-funroll-loops")))
long combine_auto_unroll(const vector<int>& v) {
    long sum = 0;
    const int* const end = v.data() + v.size();
    for (const int* i = v.data(); i < end; i++) {
        sum += *i;
    }
    return sum;
}

/* Unroll loop by 2, 2-way parallelism */
long combine_unroll_2_parallel_2(const vector<int>& v) {
    long sum1 = 0;
    long sum2 = 0;
    const int* i;
    const int* end = v.data() + v.size();
    for (i = v.data(); i < end; i += 2) {
        sum1 = sum1 + *i;
        sum2 = sum2 + *(i + 1);
    }
    for (; i < end; i++) {
        sum1 += *i;
    }
    return sum1 + sum2;
}

/* Unroll loop by 3, 3-way parallelism */
long combine_unroll_3_parallel_3(const vector<int>& v) {
    long sum1 = 0;
    long sum2 = 0;
    long sum3 = 0;
    const int* i;
    const int* end = v.data() + v.size();
    for (i = v.data(); i < end; i += 3) {
        sum1 = sum1 + *i;
        sum2 = sum2 + *(i + 1);
        sum3 = sum3 + *(i + 2);
    }
    for (; i < end; i++) {
        sum1 += *i;
    }
    return sum1 + sum2 + sum3;
}

/* Change associativity of combining operation */
long combine_unroll_2_reassociate(const vector<int>& v) {
    long sum = 0;
    const int* i;
    const int* end = v.data() + v.size();
    for (i = v.data(); i < end; i += 2) {
        sum += *i + *(i+1);
    }
    for (; i < end; i++) {
        sum += *i;
    }
    return sum;
}

/* Final version */
long combine_final(const vector<int>& v) {
    long sum = 0;
    const int* i;
    const int* end = v.data() + v.size();
    for (i = v.data(); i < end; i += 4) {
        sum += *i + *(i + 1) + *(i + 2) + *(i + 3);
    }
    for (; i < end; i++) {
        sum += *i;
    }
    return sum;
}

int main() {

    google::InitGoogleLogging("optimization_demo");
    google::SetStderrLogging(google::INFO);

    int size = 1000000;

    vector<int> v;
    v.reserve(size);
    for (int i = 0; i < size; i++) {
        v.push_back(i);
    }

    TimeRecorder time_recorder;
    time_recorder.start();

    long result_trival = combine_trival(v);
    time_recorder.addTimePoint("trival");
    cout << "result_trival : " << result_trival << endl;

    long result_trival_bad = 0;
    combine_trival_bad(v, result_trival_bad);
    time_recorder.addTimePoint("trival_bad");
    cout << "result_trival_bad : " << result_trival_bad << endl;

    long result_outofloop = combine_outofloop(v);
    time_recorder.addTimePoint("outofloop");
    cout << "result_outofloop : " << result_outofloop << endl;

    long result_direct_access = combine_direct_access(v);
    time_recorder.addTimePoint("direct_access");
    cout << "result_direct_access : " << result_direct_access << endl;

    long result_unroll_2 = combine_unroll_2(v);
    time_recorder.addTimePoint("unroll_2");
    cout << "result_unroll_2 : " << result_unroll_2 << endl;

    long result_unroll_3 = combine_unroll_3(v);
    time_recorder.addTimePoint("unroll_3");
    cout << "result_unroll_3 : " << result_unroll_3 << endl;

    long result_unroll_4 = combine_unroll_4(v);
    time_recorder.addTimePoint("unroll_4");
    cout << "result_unroll_4 : " << result_unroll_4 << endl;

    long result_auto_unroll = combine_auto_unroll(v);
    time_recorder.addTimePoint("auto_unroll");
    cout << "result_auto_unroll : " << result_auto_unroll << endl;

    long result_unroll_2_parallel_2 = combine_unroll_2_parallel_2(v);
    time_recorder.addTimePoint("u_2_p_2");
    cout << "result_unroll_2_parallel_2 : " << result_unroll_2_parallel_2 << endl;

    long result_unroll_3_parallel_3 = combine_unroll_3_parallel_3(v);
    time_recorder.addTimePoint("u_3_p_3");
    cout << "result_unroll_3_parallel_3 : " << result_unroll_3_parallel_3 << endl;

    long result_unroll_2_reassociate = combine_unroll_2_reassociate(v);
    time_recorder.addTimePoint("u_2_reasso");
    cout << "result_unroll_2_reassociate : " << result_unroll_2_reassociate << endl;

    long result_final_version = combine_final(v);
    time_recorder.addTimePoint("final");
    cout << "result_final_version : " << result_final_version << endl;

    CHECK_EQ(result_trival, result_trival_bad);
    CHECK_EQ(result_trival, result_outofloop);
    CHECK_EQ(result_trival, result_direct_access);
    CHECK_EQ(result_trival, result_unroll_2);
    CHECK_EQ(result_trival, result_unroll_3);
    CHECK_EQ(result_trival, result_unroll_4);
    CHECK_EQ(result_trival, result_auto_unroll);
    CHECK_EQ(result_trival, result_unroll_2_parallel_2);
    CHECK_EQ(result_trival, result_unroll_3_parallel_3);
    CHECK_EQ(result_trival, result_unroll_2_reassociate);
    CHECK_EQ(result_trival, result_final_version);

    time_recorder.print();

    return 0;
}