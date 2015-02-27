#include "bmi.h"


#define initialized_or_return(model) { \
  if (!model || !model->self) return BMI_FAILURE; \
}

#define call_bmi_and_return(model, func, ...) { \
  initialized_or_return(model); \
  return model->func (model->self, ##__VA_ARGS__); \
}


int
BMI_Initialize(BMI_Model *model, const char * config_file)
{
  return model->initialize(config_file, &(model->self));
}


int BMI_Update(BMI_Model *model) {
  call_bmi_and_return(model, update);
}


int BMI_Update_until(BMI_Model *model, double time) {
  call_bmi_and_return(model, update_until, time);
}


int BMI_Update_frac(BMI_Model *model, double fraction) {
  call_bmi_and_return(model, update_frac, fraction);
}


int BMI_Finalize(BMI_Model *model) {
  call_bmi_and_return(model, finalize);
}


int BMI_Run_model(BMI_Model *model) {
  call_bmi_and_return(model, run_model);
}


int BMI_Get_component_name(BMI_Model* model, char * name) {
  call_bmi_and_return(model, get_component_name, name);
}


int BMI_Get_input_var_name_count(BMI_Model * model, int * count) {
  call_bmi_and_return(model, get_input_var_name_count, count);
}


int BMI_Get_output_var_name_count(BMI_Model * model, int * count) {
  call_bmi_and_return(model, get_output_var_name_count, count);
}


int BMI_Get_input_var_names(BMI_Model * model, char ** names) {
  call_bmi_and_return(model, get_input_var_names, names);
}


int BMI_Get_output_var_names(BMI_Model * model, char ** names) {
  call_bmi_and_return(model, get_output_var_names, names);
}


int BMI_Get_time_step(BMI_Model* model, double * dt) {
  call_bmi_and_return(model, get_time_step, dt);
}


int BMI_Get_current_time(BMI_Model* model, double * time) {
  call_bmi_and_return(model, get_current_time, time);
}


int BMI_Get_var_type(BMI_Model * model, const char * name, char * type) {
  call_bmi_and_return(model, get_var_type, name, type);
}


int BMI_Get_var_units(BMI_Model * model, const char * name, char * units) {
  call_bmi_and_return(model, get_var_units, name, units);
}


int BMI_Get_var_rank(BMI_Model * model, const char * name, int * rank) {
  call_bmi_and_return(model, get_var_rank, name, rank);
}


int BMI_Get_grid_shape(BMI_Model * model, const char * name, int * shape) {
  call_bmi_and_return(model, get_grid_shape, name, shape);
}


int BMI_Get_grid_spacing(BMI_Model * model, const char * name,
    double * spacing) {
  call_bmi_and_return(model, get_grid_spacing, name, spacing);
}


int BMI_Get_grid_origin(BMI_Model * model, const char * name,
    double * origin) {
  call_bmi_and_return(model, get_grid_origin, name, origin);
}


int BMI_Get_value(BMI_Model * model, const char * name, void * buffer) {
  call_bmi_and_return(model, get_value, name, buffer);
}


int BMI_Get_value_ptr(BMI_Model * model, const char * name, void **ptr) {
  call_bmi_and_return(model, get_value_ptr, name, ptr);
}


int BMI_Set_value(BMI_Model * model, const char * name, void * buffer) {
  call_bmi_and_return(model, set_value, name, buffer);
}


int BMI_Set_value_at_indices(BMI_Model * model, const char * name,
    int * indices, int len, void * buffer) {
  call_bmi_and_return(model, set_value_at_indices, name, indices, len, buffer);
}
