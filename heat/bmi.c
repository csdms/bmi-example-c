#include "bmi.h"
#include <stdio.h>

int
BMI_Initialize(BMI_Model *model, const char * config_file)
{
  return model->Initialize(config_file, &(model->self));
}


int
BMI_Update(BMI_Model *model)
{
  if (model && model->self)
    return model->Update(model->self);
  else
    return 1;
}


int
BMI_Update_until(BMI_Model *model, double time)
{
  return model->Update_until(model->self, time);
}


int
BMI_Update_frac(BMI_Model *model, double fraction)
{
  return model->Update_frac(model->self, fraction);
}


int
BMI_Finalize(BMI_Model *model)
{
  return model->Finalize(model->self);
}


int
BMI_Run_model(BMI_Model *model)
{
  if (model && model->self)
    return model->Run_model(model->self);
  else
    return 1;
}


int
BMI_Get_component_name(BMI_Model* model, char * name)
{
  if (model && model->self)
    return model->Get_component_name(model->self, name);
  else
    return 1;
}

int
BMI_Get_input_var_name_count(BMI_Model * model, int * count)
{
  return model->Get_input_var_name_count(model->self, count);
}


int
BMI_Get_output_var_name_count(BMI_Model * model, int * count)
{
  return model->Get_output_var_name_count(model->self, count);
}


int
BMI_Get_input_var_names(BMI_Model * model, char ** names)
{
  return model->Get_input_var_names(model->self, names);
}


int
BMI_Get_output_var_names(BMI_Model * model, char ** names)
{
  return model->Get_output_var_names(model->self, names);
}


int
BMI_Get_time_step(BMI_Model* model, double * dt)
{
  if (model && model->self)
    return model->Get_time_step(model->self, dt);
  else
    return 1;
}


int
BMI_Get_current_time(BMI_Model* model, double * time)
{
  if (model && model->self)
    return model->Get_current_time(model->self, time);
  else
    return 1;
}


int
BMI_Get_var_type(BMI_Model * model, const char * name, char * type)
{
  if (model && model->self)
    return model->Get_var_type(model->self, name, type);
  else
    return 1;
}


int
BMI_Get_var_units(BMI_Model * model, const char * name, char * units)
{
  if (model && model->self)
    return model->Get_var_units(model->self, name, units);
  else
    return 1;
}


int
BMI_Get_var_rank(BMI_Model * model, const char * name, int * rank)
{
  if (model && model->self)
    return model->Get_var_rank(model->self, name, rank);
  else
    return 1;
}


int
BMI_Get_grid_shape(BMI_Model * model, const char * name, int * shape)
{
  if (model && model->self)
    return model->Get_grid_shape(model->self, name, shape);
  else
    return 1;
}


int
BMI_Get_grid_spacing(BMI_Model * model, const char * name, double * spacing)
{
  if (model && model->self)
    return model->Get_grid_spacing(model->self, name, spacing);
  else
    return 1;
}


int
BMI_Get_grid_origin(BMI_Model * model, const char * name, double * origin)
{
  if (model && model->self)
    return model->Get_grid_origin(model->self, name, origin);
  else
    return 1;
}


int
BMI_Get_value(BMI_Model * model, const char * name, void * buffer)
{
  if (model && model->self)
    return model->Get_value(model->self, name, buffer);
  else
    return 1;
}


int
BMI_Get_value_ptr(BMI_Model * model, const char * name, void **ptr)
{
  if (model && model->self)
    return model->Get_value_ptr(model->self, name, ptr);
  else
    return 1;
}


int
BMI_Set_value(BMI_Model * model, const char * name, void * buffer)
{
  return model->Set_value(model->self, name, buffer);
}


int
BMI_Set_value_at_indices(BMI_Model * model, const char * name, int * indices,
    int len, void * buffer)
{
  return model->Set_value_at_indices(model->self, name, indices, len, buffer);
}
