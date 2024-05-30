//
// Created by anton on 25.05.24.
//

#ifndef CRS_CRS_RUNNER_H
#define CRS_CRS_RUNNER_H

enum CRS_run_status {
    PASS,
    FAIL,
};

enum CRS_run_status CRS_run_code(struct CRS_attempt attempt);

#endif //CRS_CRS_RUNNER_H
