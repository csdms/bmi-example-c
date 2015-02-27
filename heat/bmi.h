#ifndef BMI_H_INCLUDED
#define BMI_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

#define BMI_SUCCESS (0)
#define BMI_FAILURE (1)

#define BMI_MAX_UNITS_NAME (2048)
#define BMI_MAX_COMPONENT_NAME (2048)
#define BMI_MAX_VAR_NAME (2048)


typedef struct {
  void * self;

  int (* Initialize)(const char *, void**);
  int (* Update)(void*);
  int (* Update_until)(void *, double);
  int (* Update_frac)(void *, double);
  int (* Finalize)(void *);
  int (* Run_model)(void *);

  int (* Get_component_name)(void *, char *);
  int (* Get_input_var_name_count)(void *, int *);
  int (* Get_output_var_name_count)(void *, int *);
  int (* Get_input_var_names)(void *, char **);
  int (* Get_output_var_names)(void *, char **);

  int (* Get_var_type)(void *, const char *, char *);
  int (* Get_var_units)(void *, const char *, char *);
  int (* Get_var_rank)(void *, const char *, int *);
  int (* Get_var_size)(void *, const char *, int *);
  int (* Get_var_nbytes)(void *, const char *, int *);
  int (* Get_current_time)(void *, double *);
  int (* Get_start_time)(void *, double *);
  int (* Get_end_time)(void *, double *);
  int (* Get_time_units)(void *, char *);
  int (* Get_time_step)(void *, double *);

  /* Variable getter and setter functions */
  int (* Get_value)(void *, const char *, void *);
  int (* Get_value_ptr)(void *, const char *, void **);
  int (* Get_value_at_indices)(void *, const char *, void *, int *, int);

  int (* Set_value)(void *, const char *, void *);
  int (* Set_value_ptr)(void *, const char *, void **);
  int (* Set_value_at_indices)(void *, const char *, int *, int, void *);

  /* Grid information functions */
  int (* Get_grid_type)(void *, const char *, char *);
  int (* Get_grid_shape)(void *, const char *, int *);
  int (* Get_grid_spacing)(void *, const char *, double *);
  int (* Get_grid_origin)(void *, const char *, double *);

  int (* Get_grid_x)(void *, const char *, double *);
  int (* Get_grid_y)(void *, const char *, double *);
  int (* Get_grid_z)(void *, const char *, double *);

  int (* Get_grid_cell_count)(void *, const char *, int *);
  int (* Get_grid_point_count)(void *, const char *, int *);
  int (* Get_grid_vertex_count)(void *, const char *, int *);

  int (* Get_grid_connectivity)(void *, const char *, int *);
  int (* Get_grid_offset)(void *, const char *, int *);
} BMI_Model;


int BMI_Initialize(BMI_Model*, const char *);
int BMI_Update(BMI_Model*);
int BMI_Update_until(BMI_Model *, double);
int BMI_Update_frac(BMI_Model *, double);
int BMI_Finalize(BMI_Model *);
int BMI_Run_model(BMI_Model *);

int BMI_Get_component_name(BMI_Model*, char *);
int BMI_Get_input_var_name_count(BMI_Model *, int *);
int BMI_Get_output_var_name_count(BMI_Model *, int *);
int BMI_Get_input_var_names(BMI_Model *, char **);
int BMI_Get_output_var_names(BMI_Model *, char **);

int BMI_Get_time_step(BMI_Model*, double *);
int BMI_Get_current_time(BMI_Model*, double *);

int BMI_Get_var_type(BMI_Model * model, const char * name, char * type);
int BMI_Get_var_units(BMI_Model * model, const char * name, char * units);
int BMI_Get_var_rank(BMI_Model * model, const char * name, int * rank);

int BMI_Get_grid_shape(BMI_Model * model, const char * name, int * shape);
int BMI_Get_grid_spacing(BMI_Model * model, const char * name, double * spacing);
int BMI_Get_grid_origin(BMI_Model * model, const char * name, double * origin);

int BMI_Get_value(BMI_Model *, const char *, void *);
int BMI_Get_value_ptr(BMI_Model *, const char *, void **);

int BMI_Set_value(BMI_Model *, const char *, void *);
int BMI_Set_value_at_indices(BMI_Model *, const char *, int *, int, void *);

#if defined(__cplusplus)
}
#endif

#endif
