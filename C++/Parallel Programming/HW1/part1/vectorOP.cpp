#include "PPintrin.h"

// implementation of absSerial(), but it is vectorized using PP intrinsics
void absVector(float *values, float *output, int N)
{
  __pp_vec_float x;
  __pp_vec_float result;
  __pp_vec_float zero = _pp_vset_float(0.f);
  __pp_mask maskAll, maskIsNegative, maskIsNotNegative;

  //  Note: Take a careful look at this loop indexing.  This example
  //  code is not guaranteed to work when (N % VECTOR_WIDTH) != 0.
  //  Why is that the case?
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {

    // All ones
    maskAll = _pp_init_ones();

    // All zeros
    maskIsNegative = _pp_init_ones(0);

    // Load vector of values from contiguous memory addresses
    _pp_vload_float(x, values + i, maskAll); // x = values[i];

    // Set mask according to predicate
    _pp_vlt_float(maskIsNegative, x, zero, maskAll); // if (x < 0) {

    // Execute instruction using mask ("if" clause)
    _pp_vsub_float(result, zero, x, maskIsNegative); //   output[i] = -x;

    // Inverse maskIsNegative to generate "else" mask
    maskIsNotNegative = _pp_mask_not(maskIsNegative); // } else {

    // Execute instruction ("else" clause)
    _pp_vload_float(result, values + i, maskIsNotNegative); //   output[i] = x; }

    // Write results back to memory
    _pp_vstore_float(output + i, result, maskAll);
  }
}

void clampedExpVector(float *values, int *exponents, float *output, int N)
{
  //
  // PP STUDENTS TODO: Implement your vectorized version of
  // clampedExpSerial() here.
  //
  // Your solution should work for any value of
  // N and VECTOR_WIDTH, not just when VECTOR_WIDTH divides N
  //
  __pp_vec_float x;
  __pp_vec_int y;
  __pp_vec_float result, tmp;
  __pp_vec_float max = _pp_vset_float(9.999999);
  __pp_vec_float ones_float = _pp_vset_float(1.f);
  __pp_vec_int ones_int = _pp_vset_int(1);
  __pp_vec_float zero_float = _pp_vset_float(0.f);
  __pp_vec_int zero_int = _pp_vset_int(0);
  __pp_mask maskAll, maskIsZero, maskIsGTOne, maskIsMax;
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {
    
    if(N % VECTOR_WIDTH!=0 && i + VECTOR_WIDTH > N){
      // All ones
      maskAll = _pp_init_ones(N%VECTOR_WIDTH);
      
    }
    else{
      maskAll = _pp_init_ones();
    }
    
    result = _pp_vset_float(0.f);//reset result
    _pp_vmove_float(result, ones_float, maskAll);//result[i] = 1
    maskIsMax = _pp_init_ones(0);//reset maskIsMax
    
    _pp_vload_float(x, values + i, maskAll); // x = values[i];
    _pp_vload_int(y, exponents + i, maskAll); // y = exponents[i];

    _pp_veq_int(maskIsZero, y, zero_int, maskAll); // if (y == 0) {
    _pp_vstore_float(output + i, ones_float, maskIsZero);//output[i] = 1
    

    maskIsGTOne = _pp_mask_not(maskIsZero);//else y >= 1
    maskIsGTOne = _pp_mask_and(maskIsGTOne, maskAll);

    while(_pp_cntbits (maskIsGTOne) > 0){//  count > 0
      
      _pp_vmult_float(result, result, x, maskIsGTOne);//result[i] *= x[i]
      _pp_vsub_int(y, y, ones_int, maskIsGTOne);//y[i] -= 1
      _pp_vgt_int (maskIsGTOne, y, zero_int, maskIsGTOne);//if(y > 0)
      
    }
    
    maskIsGTOne = _pp_mask_not(maskIsZero);
    _pp_vgt_float(maskIsMax, result, max, maskIsGTOne);//if(result[i] > 9.99999)
    _pp_vmove_float(result, max, maskIsMax);//result[i] = 9.99999
    
    maskAll = _pp_init_ones();
    _pp_vstore_float(output + i, result, maskAll);//output[i] = result[i]
    
  }
  
}

// returns the sum of all elements in values
// You can assume N is a multiple of VECTOR_WIDTH
// You can assume VECTOR_WIDTH is a power of 2
float arraySumVector(float *values, int N)
{

  //
  // PP STUDENTS TODO: Implement your vectorized version of arraySumSerial here
  //
  __pp_mask maskAll;
  maskAll = _pp_init_ones();
  __pp_vec_float x;
  float sum = 0;
  __pp_vec_float local_sum = _pp_vset_float(0.f);
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {
    _pp_vload_float(x, values + i, maskAll); // x = values[i];
    _pp_vadd_float(local_sum, x, local_sum, maskAll);
  }

  for(int i =0;i<log2(VECTOR_WIDTH);i++){
    _pp_hadd_float(local_sum, local_sum);
    _pp_interleave_float(local_sum, local_sum);
  }

  return local_sum.value[0];
}