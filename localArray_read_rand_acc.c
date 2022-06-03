//
// Created by ganyush on 6/03/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <adios2_c.h>
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    adios2_adios *adios = adios2_init(MPI_COMM_WORLD, adios2_debug_mode_on);
    adios2_io *io = adios2_declare_io(adios, "Read");
    adios2_error adiosErr = adios2_set_engine(io, "BP4");
    adios2_engine *e = adios2_open(io, "localArray.bp", adios2_mode_readRandomAccess);
    size_t step=0;
    adios2_steps(&step, e);
    adios2_step_status status;

    size_t current_step;

    printf("step = %lu\n", step);
    adios2_variable *v0 =  adios2_inquire_variable(io, "v0");
    printf ("var0 %p\n", v0);
    size_t steps_start;
    adios2_variable_steps_start(&steps_start, v0);

    printf ("step start var0 %ld\n", steps_start);

    size_t steps;
    adios2_variable_steps(&steps, v0);
    printf ("steps var0 %ld\n", steps);

    adios2_variable *v1 =  adios2_inquire_variable(io, "v1");
    printf ("var1 %p\n", v1);

    adios2_variable_steps_start(&steps_start, v1);

    printf ("step start var1 %ld\n", steps_start);


    adios2_variable_steps(&steps, v1);
    printf ("steps var1 %ld\n", steps);


    const size_t Nglobal = 40;
    int8_t v0_buff[Nglobal];
    int8_t v1_buff[Nglobal];
    
    printf("Step is not selected \n");
    printf("v0 : \n");
    adios2_get(e, v0, v0_buff, adios2_mode_sync);
    for (int i = 0; i < Nglobal; i++){
	    printf(" %d ", v0_buff[i]);
    }
     
    printf("\n");

    printf("v1 : \n");
    adios2_get(e, v1, v1_buff, adios2_mode_sync);
    for (int i = 0; i < Nglobal; i++){
            printf(" %d ", v1_buff[i]);
    }

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    for (int step = 0; step < 5; step++){
	memset(v0_buff, 255, Nglobal);
	memset(v1_buff, 255, Nglobal);
        adios2_error err0 = adios2_set_step_selection(v0, step, 1);

	if (err0 == 0){
            printf("v0 step %d : \n", step);
            adios2_get(e, v0, v0_buff, adios2_mode_sync);
            for (int i = 0; i < Nglobal; i++){
                   printf(" %d ", v0_buff[i]);
            }

        printf("\n");
	}

        adios2_error err1 = adios2_set_step_selection(v1, step, 1);
	if (err1 == 0){
            printf("v1 step %d : \n", step);
            adios2_get(e, v1, v1_buff, adios2_mode_sync);
            for (int i = 0; i < Nglobal; i++){
                    printf(" %d ", v1_buff[i]);
            }

        printf("\n");
	}
    printf("\n");
    printf("\n");
    printf("\n");
    }

    MPI_Finalize();
    return 0;
}

