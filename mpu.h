#ifndef _mpu_H
#define _mpu_H

#include <stdbool.h>

typedef struct iam_t {
    int clientID;
    char role;
}iam_t;

iam_t *soa_iam_init(const char *conf_name);

void soa_iam_destroy(iam_t *iam);

int soa_iam_logon(iam_t *iam, const char *service_name, char *out, int olen);

int soa_iam_grant(iam_t *iam, const char *client_name, char *out, int olen);

int soa_iam_acl(iam_t *iam, const char *client_name, const char *method);

bool get_session(int clientID);
#endif