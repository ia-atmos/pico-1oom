/* The oracle of tst/lbx.atm: what c/src/lbx.c reads from each LBX file,
   one line per item, with a sum of its bytes. Not part of the port.
   usage: lbx DATADIR */
#include <stdio.h>
#include "lbx.h"
#include "os.h"
#include "types.h"

void hw_log_message(const char *msg) { fputs(msg, stdout); }
void hw_log_warning(const char *msg) { fputs(msg, stdout); }
void hw_log_error(const char *msg) { fputs(msg, stdout); }

int main(int argc, char **argv)
{
    os_set_path_data(argv[1]);
    lbxfile_init();
    for (lbxfile_e f = 0; f < LBXFILE_NUM; ++f) {
        int n = lbxfile_num_items(f);
        printf("%s type %i items %i\n", lbxfile_name(f), lbxfile_type(f), n);
        for (int i = 0; i < n; ++i) {
            uint32_t len, sum = 0;
            uint8_t *p = lbxfile_item_get_with_len(f, i, &len);
            char name[33];
            const char *q = lbxfile_item_name(f, i);
            int k;
            for (k = 0; (k < 32) && q[k]; ++k) {
                name[k] = q[k];
            }
            name[k] = 0;
            for (uint32_t j = 0; j < len; ++j) {
                sum = (sum * 31 + p[j]) & 0xffffff;
            }
            printf("  %i '%s' offs %i len %i/%u sum %u\n", i, name, lbxfile_item_offs(f, i), lbxfile_item_len(f, i), len, sum);
            lbxfile_item_release(f, p);
        }
        lbxfile_item_release_file(f);
    }
    lbxfile_shutdown();
    return 0;
}
