#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "bmi_heat.h"
#include "heat.h"


#define BMI_HEAT_INPUT_VAR_NAME_COUNT 1
#define BMI_HEAT_OUTPUT_VAR_NAME_COUNT 1


const char *output_var_names[BMI_HEAT_OUTPUT_VAR_NAME_COUNT] = {
  "plate_surface__temperature"
};


const char *input_var_names[BMI_HEAT_INPUT_VAR_NAME_COUNT] = {
  "plate_surface__temperature"
};


int
BMI_HEAT_Initialize (const char *file, void ** handle)
{
  HeatModel * self = NULL;

  if (!handle)
    return BMI_FAILURE;

  if (file)
    self = heat_from_input_file (file);
  else
    self = heat_from_default ();

  *handle = (void *) self;

  return BMI_SUCCESS;
}


int
BMI_HEAT_Update (void *self)
{
  heat_advance_in_time ((HeatModel *) self);

  return BMI_SUCCESS;
}


int
BMI_HEAT_Update_frac (void *self, double f)
{
  if (f>0) {
    double dt;

    BMI_HEAT_Get_time_step (self, &dt);

    ((HeatModel *)self)->dt = f * dt;

    BMI_HEAT_Update (self);

    ((HeatModel *)self)->dt = dt;
  }

  return BMI_SUCCESS;
}


int
BMI_HEAT_Update_until (void *self, double t)
{
  {
    double dt;
    double now;

    BMI_HEAT_Get_time_step (self, &dt);
    BMI_HEAT_Get_current_time (self, &now);

    {
      int n;
      const double n_steps = (t - now) / dt;
      for (n=0; n<(int)n_steps; n++) {
        BMI_HEAT_Update (self);
      }

      BMI_HEAT_Update_frac (self, n_steps - (int)n_steps);
    }
  }

  return BMI_SUCCESS;
}


int
BMI_HEAT_Finalize (void *self)
{
  if (self)
    heat_free (self);

  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_var_type (void *self, const char *name, char * type)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    strncpy(type, "double", 2048);
    return BMI_SUCCESS;
  }
  else {
    type[0] = '\0';
    return BMI_FAILURE;
  }
}


int
BMI_HEAT_Get_var_units (void *self, const char *name, char * units)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    strncpy (units, "K", BMI_MAX_UNITS_NAME);
    return BMI_SUCCESS;
  }
  else {
    units[0] = '\0';
    return BMI_FAILURE;
  }
}


int
BMI_HEAT_Get_var_rank (void *self, const char *name, int * rank)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    *rank = 2;
    return BMI_SUCCESS;
  }
  else {
    *rank = -1;
    return BMI_FAILURE;
  }
}


int
BMI_HEAT_Get_var_size (void *self, const char *name, int * size)
{
  int status = BMI_FAILURE;

  if (strcmp (name, "plate_surface__temperature") == 0) {
    *size = ((HeatModel *)self)->shape[0] * ((HeatModel *)self)->shape[1];
    status = BMI_SUCCESS;
  }

  return status;
}


int
BMI_HEAT_Get_var_nbytes (void *self, const char *name, int * nbytes)
{
  int status = BMI_FAILURE;

  {
    int size = 0;

    status = BMI_HEAT_Get_var_size (self, name, &size);
    if (status == BMI_FAILURE)
      return status;

    *nbytes = sizeof (double) * size;
    status = BMI_SUCCESS;
  }

  return status;
}


int
BMI_HEAT_Get_grid_shape (void *self, const char *name, int * shape)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    shape[0] = ((HeatModel *)self)->shape[0];
    shape[1] = ((HeatModel *)self)->shape[1];
  }

  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_grid_spacing (void *self, const char *name, double * spacing)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    spacing[0] = ((HeatModel *)self)->spacing[0];
    spacing[1] = ((HeatModel *)self)->spacing[0];
  }

  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_grid_origin (void *self, const char *name, double * origin)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    origin[0] = 0.;
    origin[1] = 0.;
  }

  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_grid_type (void *self, const char *name, char * type)
{
  int status = BMI_FAILURE;

  {
    if (strcmp (name, "plate_surface__temperature") == 0) {
      strncpy(type, "uniform_rectilinear", 2048);
      status = BMI_SUCCESS;
    }
    else {
      type[0] = '\0';
      status = BMI_FAILURE;
    }
  }

  return status;
}


int
BMI_HEAT_Get_value (void *self, const char *name, void *dest)
{
  int status = BMI_FAILURE;

  {
    void *src = NULL;
    int nbytes = 0;

    status = BMI_HEAT_Get_value_ptr (self, name, &src);
    if (status == BMI_FAILURE)
      return status;

    status = BMI_HEAT_Get_var_nbytes (self, name, &nbytes);
    if (status == BMI_FAILURE)
      return status;

    memcpy (dest, src, nbytes);
  }

  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_value_ptr (void *self, const char *name, void **dest)
{
  int status = BMI_FAILURE;

  {
   void *src = NULL;

    if (strcmp (name, "plate_surface__temperature")==0) {
      src = ((HeatModel *) self)->z[0];
    }

    *dest = src;

    if (src)
      status = BMI_SUCCESS;
  }

  return status;
}


int
BMI_HEAT_Get_value_at_indices (void *self, const char *name, void *dest,
    int * inds, int len)
{
  int status = BMI_FAILURE;

  {
    void *src = NULL;
    const int itemsize = sizeof(double);

    status = BMI_HEAT_Get_value_ptr (self, name, &src);
    if (status == BMI_FAILURE)
      return status;

    {
      /* Copy the data */
      int i;
      int offset;
      void * ptr;
      for (i=0, ptr=dest; i<len; i++, ptr+=itemsize) {
        offset = inds[i] * itemsize;
        memcpy (ptr, src + offset, itemsize);
      }
    }
  }

  return BMI_SUCCESS;
}


int
BMI_HEAT_Set_value (void *self, const char *name, void *array)
{
  int status = BMI_FAILURE;

  {
    void * dest = NULL;
    int nbytes = 0;

    status = BMI_HEAT_Get_value_ptr (self, name, &dest);
    if (status == BMI_FAILURE)
      return status;
    
    status = BMI_HEAT_Get_var_nbytes (self, name, &nbytes);
    if (status == BMI_FAILURE)
      return status;

    memcpy (dest, array, nbytes);

    status = BMI_SUCCESS;
  }

  return status;
}


int
BMI_HEAT_Set_value_at_indices (void *self, const char *name, int * inds, int len,
    void *src)
{
  int status = BMI_FAILURE;

  {
    void * to = NULL;
    const int itemsize = sizeof(double);

    status = BMI_HEAT_Get_value_ptr (self, name, &to);
    if (status == BMI_FAILURE)
      return status;

    { /* Copy the data */
      int i;
      int offset;
      void * ptr;
      for (i=0, ptr=src; i<len; i++, ptr+=itemsize) {
        offset = inds[i] * itemsize;
        memcpy (to + offset, ptr, itemsize);
      }
    }
  }

  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_component_name (void *self, char * name)
{
  strncpy (name, "The 2D Heat Equation", BMI_MAX_COMPONENT_NAME);
  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_input_var_name_count (void *self, int * count)
{
  *count = BMI_HEAT_INPUT_VAR_NAME_COUNT;
  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_input_var_names (void *self, char ** names)
{
  int i;
  for (i=0; i<BMI_HEAT_INPUT_VAR_NAME_COUNT; i++) {
    strncpy (names[i], input_var_names[i], BMI_MAX_VAR_NAME);
  }
  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_output_var_name_count (void *self, int * count)
{
  *count = BMI_HEAT_OUTPUT_VAR_NAME_COUNT;
  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_output_var_names (void *self, char ** names)
{
  int i;
  for (i=0; i<BMI_HEAT_OUTPUT_VAR_NAME_COUNT; i++) {
    strncpy (names[i], output_var_names[i], BMI_MAX_VAR_NAME);
  }
  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_start_time (void *self, double * time)
{
  if (time) {
    *time = 0.;
    return BMI_SUCCESS;
  }
  else {
    return BMI_FAILURE;
  }
}


int
BMI_HEAT_Get_end_time (void *self, double * time)
{
  *time = ((HeatModel *)self)->t_end;
  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_current_time (void *self, double * time)
{
  *time = ((HeatModel *)self)->t;
  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_time_step (void *self, double * dt)
{
  *dt = ((HeatModel *)self)->dt;
  return BMI_SUCCESS;
}


int
BMI_HEAT_Get_time_units (void *self, char * units)
{
  strncpy (units, "-", BMI_MAX_UNITS_NAME);
  return BMI_SUCCESS;
}
