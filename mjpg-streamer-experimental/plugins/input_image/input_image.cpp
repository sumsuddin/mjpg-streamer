#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dlfcn.h>
#include <pthread.h>

#include "input_image.h"

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

/* private functions and variables to this plugin */
static globals     *pglobal;

#define INPUT_PLUGIN_NAME "Image Input plugin"
static char plugin_name[] = INPUT_PLUGIN_NAME;

/*** plugin interface functions ***/

/******************************************************************************
Description.: parse input parameters
Input Value.: param contains the command line string and a pointer to globals
Return Value: 0 if everything is ok
******************************************************************************/


int input_init(input_parameter *param, int plugin_no)
{
    pglobal = param->global;

    return 0;

    fatal_error:
    closelog();
    exit(EXIT_FAILURE);
}

/******************************************************************************
Description.: stops the execution of the worker thread
Input Value.: -
Return Value: 0
******************************************************************************/
int input_stop(int id)
{
    return 0;
}

/******************************************************************************
Description.: starts the worker thread and allocates memory
Input Value.: -
Return Value: 0
******************************************************************************/
int input_run(int id)
{
    input * in = &pglobal->in[id];

    in->buf = NULL;
    in->size = 0;
    return 0;
}

int input::set_image(unsigned char *buffer, int buffer_size, int id) {
    if (!pglobal->stop) {
        input * in = &pglobal->in[id];

        /* copy JPG picture to global buffer */
        pthread_mutex_lock(&in->db);


        // TODO: what to do if imencode returns an error?

        // std::vector is guaranteed to be contiguous
        in->buf = buffer;
        in->size = buffer_size;

        /* signal fresh_frame */
        pthread_cond_broadcast(&in->db_update);
        pthread_mutex_unlock(&in->db);
        return 0;
    }
    return -1;
}

int input::init(input_parameter *param, int id) {
    return input_init(param, id);
}
int input::stop(int id) {
    return input_stop(id);
}
int input::run(int id) {
    return input_run(id);
}


int input::cmd(int plugin, unsigned int control_id, unsigned int group, int value, char *value_str) {
    return -1;
}