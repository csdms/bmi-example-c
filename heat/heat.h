#ifndef HEAT_H_INCLUDED
#define HEAT_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif


typedef struct {
  double alpha;
  double dt;
  double t;
  double t_end;

  int shape[2];
  double spacing[2];
  double **z;

  double **temp_z;
} HeatModel;


extern HeatModel * heat_from_input_file (const char * filename);
extern HeatModel * heat_from_default (void);
extern int heat_advance_in_time (HeatModel * self);
extern int heat_solve_2d (double ** z, int shape[2], double spacing[2],
    double alpha, double dt, double ** out);
extern int heat_free (HeatModel *self);


#if defined(__cplusplus)
}
#endif

#endif
