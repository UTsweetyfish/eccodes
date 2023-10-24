/*
 * (C) Copyright 2005- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
 * virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
 */

/********************************************
 *  Enrico Fucile
 *********************************************/

#include "grib_api_internal.h"
/*
   This is used by make_class.pl

   START_CLASS_DEF
   CLASS      = accessor
   SUPER      = grib_accessor_class_double
   IMPLEMENTS = unpack_double;pack_double
   IMPLEMENTS = init
   MEMBERS=const char* longitude
   END_CLASS_DEF

 */

/* START_CLASS_IMP */

/*

Don't edit anything between START_CLASS_IMP and END_CLASS_IMP
Instead edit values between START_CLASS_DEF and END_CLASS_DEF
or edit "accessor.class" and rerun ./make_class.pl

*/

static int pack_double(grib_accessor*, const double* val, size_t* len);
static int unpack_double(grib_accessor*, double* val, size_t* len);
static void init(grib_accessor*, const long, grib_arguments*);

typedef struct grib_accessor_g2lon
{
    grib_accessor att;
    /* Members defined in gen */
    /* Members defined in double */
    /* Members defined in g2lon */
    const char* longitude;
} grib_accessor_g2lon;

extern grib_accessor_class* grib_accessor_class_double;

static grib_accessor_class _grib_accessor_class_g2lon = {
    &grib_accessor_class_double,                      /* super */
    "g2lon",                      /* name */
    sizeof(grib_accessor_g2lon),  /* size */
    0,                           /* inited */
    0,                           /* init_class */
    &init,                       /* init */
    0,                  /* post_init */
    0,                    /* destroy */
    0,                       /* dump */
    0,                /* next_offset */
    0,              /* get length of string */
    0,                /* get number of values */
    0,                 /* get number of bytes */
    0,                /* get offset to bytes */
    0,            /* get native type */
    0,                /* get sub_section */
    0,               /* pack_missing */
    0,                 /* is_missing */
    0,                  /* pack_long */
    0,                /* unpack_long */
    &pack_double,                /* pack_double */
    0,                 /* pack_float */
    &unpack_double,              /* unpack_double */
    0,               /* unpack_float */
    0,                /* pack_string */
    0,              /* unpack_string */
    0,          /* pack_string_array */
    0,        /* unpack_string_array */
    0,                 /* pack_bytes */
    0,               /* unpack_bytes */
    0,            /* pack_expression */
    0,              /* notify_change */
    0,                /* update_size */
    0,             /* preferred_size */
    0,                     /* resize */
    0,      /* nearest_smaller_value */
    0,                       /* next accessor */
    0,                    /* compare vs. another accessor */
    0,      /* unpack only ith value (double) */
    0,       /* unpack only ith value (float) */
    0,  /* unpack a given set of elements (double) */
    0,   /* unpack a given set of elements (float) */
    0,     /* unpack a subarray */
    0,                      /* clear */
    0,                 /* clone accessor */
};


grib_accessor_class* grib_accessor_class_g2lon = &_grib_accessor_class_g2lon;

/* END_CLASS_IMP */

static void init(grib_accessor* a, const long l, grib_arguments* c)
{
    grib_accessor_g2lon* self = (grib_accessor_g2lon*)a;
    int n                     = 0;

    self->longitude = grib_arguments_get_name(grib_handle_of_accessor(a), c, n++);
}

static int unpack_double(grib_accessor* a, double* val, size_t* len)
{
    grib_accessor_g2lon* self = (grib_accessor_g2lon*)a;
    int ret                   = 0;
    long longitude;

    if ((ret = grib_get_long(grib_handle_of_accessor(a), self->longitude, &longitude)) != GRIB_SUCCESS)
        return ret;

    if (longitude == GRIB_MISSING_LONG) {
        *val = GRIB_MISSING_DOUBLE;
        return GRIB_SUCCESS;
    }

    *val = ((double)longitude) / 1000000.0;

    return GRIB_SUCCESS;
}

static int pack_double(grib_accessor* a, const double* val, size_t* len)
{
    grib_accessor_g2lon* self = (grib_accessor_g2lon*)a;
    long longitude;
    double value = *val;

    if (value == GRIB_MISSING_DOUBLE) {
        longitude = GRIB_MISSING_LONG;
    }
    else {
        if (value < 0)
            value += 360;
        longitude = (long)(value * 1000000);
    }
    return grib_set_long(grib_handle_of_accessor(a), self->longitude, longitude);
}