#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define CHAR_CAST (char *)
#else
#define CHAR_CAST
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "heat.h"
#include <bmi.h>
#include "bmi_heat.h"

#define INPUT_VAR_NAME_COUNT 1
#define OUTPUT_VAR_NAME_COUNT 1


static const char *output_var_names[OUTPUT_VAR_NAME_COUNT] = {
  "plate_surface__temperature"
};


static const char *input_var_names[INPUT_VAR_NAME_COUNT] = {
  "plate_surface__temperature"
};


static int
Get_start_time (Bmi *self, double * time)
{
  *time = 0.;
  return BMI_SUCCESS;
}


static int
Get_end_time (Bmi *self, double * time)
{
  *time = ((HeatModel *)self->data)->t_end;
  return BMI_SUCCESS;
}


static int
Get_time_step (Bmi *self, double * dt)
{
  *dt = ((HeatModel *)self->data)->dt;
  return BMI_SUCCESS;
}


static int
Get_time_units (Bmi *self, char * units)
{
  strncpy (units, "s", BMI_MAX_UNITS_NAME);
  return BMI_SUCCESS;
}


static int
Get_current_time (Bmi *self, double * time)
{
  *time = ((HeatModel *)self->data)->t;
  return BMI_SUCCESS;
}


static int
Initialize (Bmi *self, const char *file)
{
  HeatModel *heat;

  if (!self)
    return BMI_FAILURE;
  else
    heat = (HeatModel *) self->data;

  if (file)
    heat_from_input_file(&heat, file);
  else
    heat_from_default(&heat);

  return BMI_SUCCESS;
}


static int
Update (Bmi *self)
{
  heat_advance_in_time ((HeatModel *) self->data);

  return BMI_SUCCESS;
}


static int
Update_until (Bmi *self, double t)
{
  {
    double dt;
    double now;

    Get_time_step (self, &dt);
    Get_current_time (self, &now);

    {
      int n;
      double frac;
      const double n_steps = (t - now) / dt;
      for (n=0; n<(int)n_steps; n++) {
        Update (self);
      }

      frac = n_steps - (int)n_steps;
      ((HeatModel *)self->data)->dt = frac * dt;
      Update (self);
      ((HeatModel *)self->data)->dt = dt;
    }
  }

  return BMI_SUCCESS;
}


static int
Finalize (Bmi *self)
{
  if (self) {
    heat_free ((HeatModel*)(self->data));
    self->data = (void*)new_bmi_heat();
  }

  return BMI_SUCCESS;
}


static int
Get_grid_rank (Bmi *self, int grid, int * rank)
{
  if (grid == 0) {
    *rank = 2;
    return BMI_SUCCESS;
  }
  else {
    *rank = -1;
    return BMI_FAILURE;
  }
}


static int
Get_grid_size (Bmi *self, int grid, int * size)
{
  if (grid == 0) {
    *size = ((HeatModel *)self->data)->shape[0] * ((HeatModel *)self->data)->shape[1];
    return BMI_SUCCESS;
  }
  else {
    *size = -1;
    return BMI_FAILURE;
  }
}


static int
Get_grid_shape (Bmi *self, int grid, int * shape)
{
  if (grid == 0) {
    shape[0] = ((HeatModel *)self->data)->shape[0];
    shape[1] = ((HeatModel *)self->data)->shape[1];
  }

  return BMI_SUCCESS;
}


static int
Get_grid_spacing (Bmi *self, int grid, double * spacing)
{
  if (grid == 0) {
    spacing[0] = ((HeatModel *)self->data)->spacing[0];
    spacing[1] = ((HeatModel *)self->data)->spacing[1];
  }

  return BMI_SUCCESS;
}


static int
Get_grid_origin (Bmi *self, int grid, double * origin)
{
  if (grid == 0) {
    origin[0] = 0.;
    origin[1] = 0.;
  }

  return BMI_SUCCESS;
}


static int
Get_grid_type (Bmi *self, int grid, char * type)
{
  int status = BMI_FAILURE;

  if (grid == 0) {
    strncpy(type, "uniform_rectilinear", BMI_MAX_TYPE_NAME);
    status = BMI_SUCCESS;
  }
  else {
    type[0] = '\0';
    status = BMI_FAILURE;
  }

  return status;
}


static int
Get_var_grid (Bmi *self, const char *name, int * grid)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    *grid = 0;
    return BMI_SUCCESS;
  }
  else {
    *grid = -1;
    return BMI_FAILURE;
  }
}


static int
Get_var_type (Bmi *self, const char *name, char * type)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    strncpy(type, "double", BMI_MAX_TYPE_NAME);
    return BMI_SUCCESS;
  }
  else {
    type[0] = '\0';
    return BMI_FAILURE;
  }
}


static int
Get_var_itemsize (Bmi *self, const char *name, int * size)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    *size = sizeof(double);
    return BMI_SUCCESS;
  }
  else {
    *size = 0;
    return BMI_FAILURE;
  }
}


static int
Get_var_units (Bmi *self, const char *name, char * units)
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


static int
Get_var_nbytes (Bmi *self, const char *name, int * nbytes)
{
  int status = BMI_FAILURE;

  {
    int size = 0;
    int grid;

    *nbytes = -1;

    if (Get_var_grid(self, name, &grid) == BMI_FAILURE)
      return BMI_FAILURE;

    if (Get_grid_size (self, grid, &size) == BMI_FAILURE)
      return BMI_FAILURE;

    *nbytes = sizeof (double) * size;
    status = BMI_SUCCESS;
  }

  return status;
}


static int
Get_var_location (Bmi *self, const char *name, char *location)
{
  if (strcmp (name, "plate_surface__temperature") == 0) {
    strncpy (location, "node", BMI_MAX_UNITS_NAME);
    return BMI_SUCCESS;
  }
  else {
    location[0] = '\0';
    return BMI_FAILURE;
  }
}


static int
Get_value_ptr (Bmi *self, const char *name, void **dest)
{
  int status = BMI_FAILURE;

  {
   void *src = NULL;

    if (strcmp (name, "plate_surface__temperature")==0) {
      src = ((HeatModel *) self->data)->z[0];
    }

    *dest = src;

    if (src)
      status = BMI_SUCCESS;
  }

  return status;
}


static int
Get_value (Bmi *self, const char *name, void *dest)
{
  int status = BMI_FAILURE;

  {
    void *src = NULL;
    int nbytes = 0;

    status = Get_value_ptr (self, name, &src);
    if (status == BMI_FAILURE)
      return status;

    status = Get_var_nbytes (self, name, &nbytes);
    if (status == BMI_FAILURE)
      return status;

    memcpy (dest, src, nbytes);
  }

  return BMI_SUCCESS;
}


static int
Get_value_at_indices (Bmi *self, const char *name, void *dest,
    int * inds, int len)
{
  int status = BMI_FAILURE;

  {
    void *src = NULL;
    const int itemsize = sizeof(double);

    status = Get_value_ptr (self, name, &src);
    if (status == BMI_FAILURE)
      return status;

    {
      /* Copy the data */
      int i;
      int offset;
      void * ptr;
      for (i=0, ptr=dest; i<len; i++, CHAR_CAST ptr+=itemsize) {
        offset = inds[i] * itemsize;
        memcpy (ptr, CHAR_CAST src + offset, itemsize);
      }
    }
  }

  return BMI_SUCCESS;
}


static int
Set_value (Bmi *self, const char *name, void *array)
{
  int status = BMI_FAILURE;

  {
    void * dest = NULL;
    int nbytes = 0;

    status = Get_value_ptr (self, name, &dest);
    if (status == BMI_FAILURE)
      return status;

    status = Get_var_nbytes (self, name, &nbytes);
    if (status == BMI_FAILURE)
      return status;

    memcpy (dest, array, nbytes);

    status = BMI_SUCCESS;
  }

  return status;
}


static int
Set_value_at_indices (Bmi *self, const char *name, int * inds, int len,
    void *src)
{
  int status = BMI_FAILURE;

  {
    void * to = NULL;
    const int itemsize = sizeof(double);

    status = Get_value_ptr (self, name, &to);
    if (status == BMI_FAILURE)
      return status;

    { /* Copy the data */
      int i;
      int offset;
      void * ptr;
      for (i=0, ptr=src; i<len; i++, CHAR_CAST ptr+=itemsize) {
        offset = inds[i] * itemsize;
        memcpy (CHAR_CAST to + offset, ptr, itemsize);
      }
    }
  }

  return BMI_SUCCESS;
}


static int
Get_component_name (Bmi *self, char * name)
{
  strncpy (name, "The 2D Heat Equation", BMI_MAX_COMPONENT_NAME);
  return BMI_SUCCESS;
}


static int
Get_input_item_count (Bmi *self, int * count)
{
  *count = INPUT_VAR_NAME_COUNT;
  return BMI_SUCCESS;
}


static int
Get_input_var_names (Bmi *self, char ** names)
{
  int i;
  for (i=0; i<INPUT_VAR_NAME_COUNT; i++) {
    strncpy (names[i], input_var_names[i], BMI_MAX_VAR_NAME);
  }
  return BMI_SUCCESS;
}


static int
Get_output_item_count (Bmi *self, int * count)
{
  *count = OUTPUT_VAR_NAME_COUNT;
  return BMI_SUCCESS;
}


static int
Get_output_var_names (Bmi *self, char ** names)
{
  int i;
  for (i=0; i<OUTPUT_VAR_NAME_COUNT; i++) {
    strncpy (names[i], output_var_names[i], BMI_MAX_VAR_NAME);
  }
  return BMI_SUCCESS;
}


HeatModel *
new_bmi_heat(void)
{
  HeatModel *data;

  data = (HeatModel*) malloc(sizeof(HeatModel));
  return data;
}


Bmi*
register_bmi_heat(Bmi *model)
{
  if (model) {
    model->data = (void*)new_bmi_heat();

    model->initialize = Initialize;
    model->update = Update;
    model->update_until = Update_until;
    model->finalize = Finalize;

    model->get_component_name = Get_component_name;
    model->get_input_item_count = Get_input_item_count;
    model->get_output_item_count = Get_output_item_count;
    model->get_input_var_names = Get_input_var_names;
    model->get_output_var_names = Get_output_var_names;

    model->get_var_grid = Get_var_grid;
    model->get_var_type = Get_var_type;
    model->get_var_itemsize = Get_var_itemsize;
    model->get_var_units = Get_var_units;
    model->get_var_nbytes = Get_var_nbytes;
    model->get_var_location = Get_var_location;

    model->get_current_time = Get_current_time;
    model->get_start_time = Get_start_time;
    model->get_end_time = Get_end_time;
    model->get_time_units = Get_time_units;
    model->get_time_step = Get_time_step;

    model->get_value = Get_value;
    model->get_value_ptr = Get_value_ptr;
    model->get_value_at_indices = Get_value_at_indices;

    model->set_value = Set_value;
    model->set_value_at_indices = Set_value_at_indices;

    model->get_grid_size = Get_grid_size;
    model->get_grid_rank = Get_grid_rank;
    model->get_grid_type = Get_grid_type;

    model->get_grid_shape = Get_grid_shape;
    model->get_grid_spacing = Get_grid_spacing;
    model->get_grid_origin = Get_grid_origin;

    model->get_grid_x = NULL;
    model->get_grid_y = NULL;
    model->get_grid_z = NULL;

    model->get_grid_node_count = Get_grid_size;
    model->get_grid_edge_count = NULL;
    model->get_grid_face_count = NULL;
    model->get_grid_edge_nodes = NULL;
    model->get_grid_face_edges = NULL;
    model->get_grid_face_nodes = NULL;
    model->get_grid_nodes_per_face = NULL;
  }

  return model;
}
