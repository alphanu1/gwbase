/*/////////////////////////////////////////////////////////////////////////////
/// @summary Implements a math library based on single-precision IEEE 754
/// floating-point numbers.
/// @author Russell Klenk (contact@russellklenk.com)
///////////////////////////////////////////////////////////////////////////80*/

#ifndef GW_MATH_HPP
#define GW_MATH_HPP

/*////////////////
//   Includes   //
////////////////*/
#include <limits>
#include "common.hpp"

/*////////////////
//  Data Types  //
////////////////*/
/// @summary Defines the state data associated with a WELL512 PRNG instance.
/// The application allocates a new instance of this structure, and initializes
/// it using the random_init() function.
struct rng_state_t
{
    uint32_t index;     /// The current index into the state block
    uint32_t state[16]; /// The RNG state data
};

/*///////////////
//  Functions  //
///////////////*/
/// @summary Determines the smaller of two floating point values.
/// @param a The first value.
/// @param b The second value.
/// @return The smaller of a or b.
float min2(float a, float b);

/// @summary Determines the larger of two floating point values.
/// @param a The first value.
/// @param b The second value.
/// @return The larger of a or b.
float max2(float a, float b);

/// @summary Determines the smallest of three floating point values.
/// @param a The first value.
/// @param b The second value.
/// @param c The third value.
/// @return The smaller of a, b and c.
float min3(float a, float b, float c);

/// @summary Determines the largest of three floating point values.
/// @param a The first value.
/// @param b The second value.
/// @param c The third value.
/// @return The largest of a, b and c.
float max3(float a, float b, float c);

/// @summary Performs linear interpolation between two scalar values.
/// @param a The value at t = 0.
/// @param b The value at t = 1.
/// @param t A normalized interpolation parameter.
/// @return The interpolated value.
float mix(float a, float b, float t);

/// @summary Clamps a value to a given range.
/// @param x The value to clamp.
/// @param a The lower-bound of the range.
/// @param b The upper-bound of the range.
/// @return The value x clamped to the range [a, b].
float clamp(float x, float a, float b);

/// @summary Determines whether two floating point values are close enough to
/// be considered equal, using the same value for absolute and relative tolerance (FLT_EPSILON).
/// @param a The first value.
/// @param b The second value.
/// @return true if a and b can be considered equal.
bool eq(float a, float b);

/// @summary Determines whether two floating point values are close enough to
/// be considered equal, using the specified absolute tolerance. This test
/// fails when both a and b are very large.
/// @param a The first value.
/// @param b The second value.
/// @param tol The absolute tolerance value.
/// @return true if a and b can be considered equal.
bool eq_abs(float a, float b, float tol);

/// @summary Determines whether two floating point values are close enough to
/// be considered equal, using the specified relative tolerance. This test
/// fails when both a and b are very small.
/// @param a The first value.
/// @param b The second value.
/// @param tol The relative tolerance value.
/// @return true if a and b can be considered equal.
bool eq_rel(float a, float b, float tol);

/// @summary Determines whether two floating point values are close enough to
/// be considered equal, using the specified absolute and relative tolerance values.
/// @param a The first value.
/// @param b The second value.
/// @param tol_a The absolute tolerance value.
/// @param tol_r The relative tolerance value.
/// @return true if a and b can be considered equal.
bool eq_com(float a, float b, float tol_a, float tol_r);

/// @summary Determines whether a floating point value has the special Not A Number value.
/// @param a The value to check.
/// @return true if a is NaN.
bool is_nan(float a);

/// @summary Determines whether a floating point value is either positive or negative infinity.
/// @param a The value to check.
/// @return true if a is either the positive or negative infinity value.
bool is_inf(float a);

/// @summary Computes the reciporical value 1/a for a given value.
/// @param a The input value.
/// @return The value 1/a. The function does not check for divide-by-zero.
float rcp(float a);

/// @summary Converts a value specified in degrees to radians.
/// @param degrees The angle measure specified in degrees.
/// @return The angle measure specified in radians.
float rad(float degrees);

/// @summary Converts a value specified in radians to degrees.
/// @param radians The angle measure specified in radians.
/// @return The angle measure specified in degrees.
float deg(float radians);

/// @summary Performs linear interpolation between two scalar values.
/// @param a The value at t = 0.
/// @param b The value at t = 1.
/// @param t A normalized interpolation parameter.
/// @return The interpolated value.
float linear(float a, float b, float t);

/// @summary Performs Bezier interpolation between two scalar values.
/// @param a The value at t = 0.
/// @param b The value at t = 1.
/// @param in_t The tangent value (slope) coming into b.
/// @param out_t The tangent value (slope) coming out of b.
/// @param t A normalized interpolation parameter.
/// @return The interpolated value.
float bezier(float  a, float b, float in_t, float out_t, float t);

/// @summary Performs Hermite interpolation between two scalar values.
/// @param a The value at t = 0.
/// @param b The value at t = 1.
/// @param in_t The tangent value (slope) coming into b.
/// @param out_t The tangent value (slope) coming out of b.
/// @param t A normalized interpolation parameter.
/// @return The interpolated value.
float hermite(float a, float b, float in_t, float out_t, float t);

/// @summary Determines the number of bytes of seed data required to seed a
/// random number generator instance.
/// @return The number of bytes required to seed a PRNG instance.
size_t random_seed_size(void);

/// @summary Initializes a PRNG instance to the default state. The RNG remains
/// unseeded; call random_seed() before requesting data from the RNG.
/// @param rng The PRNG state data to initialize.
void random_init(rng_state_t *rng);

/// @summary Supplies seed data to seed (or re-seed) a PRNG.
/// @param rng The PRNG instance to seed (or re-seed.)
/// @param seed_data Pointer to the start of a memory block containing the seed data for the PRNG.
/// @param seed_size The size of the seed data, in bytes. This value must be
/// at least the size specified by random_seed_size().
void random_seed(rng_state_t *rng, void *seed_data, size_t seed_size);

/// @summary Generates a sequence of values [start, start + count). The values are not randomized.
/// @param values Pointer to storage for an array of 32-bit unsigned integer values that will be set to the values in the sequence.
/// @param start The starting value of the sequence.
/// @param count The number of values in the sequence.
void random_sequence(uint32_t *values, uint32_t start, size_t count);

/// @summary Shuffles the values in an array using the Knuth-Fisher-Yates algorithm.
/// @param values The array of values to be shuffled.
/// @param count The number of values in @a values to shuffle.
/// @param rng The state of the random number generator to be used when shuffling the values of the array.
void random_shuffle(uint32_t *values, size_t count, rng_state_t *rng);

/// @summary Samples a set without replacement. All values in the set have
/// uniform weight; that is, all values are equally likely to be chosen. Each
/// value in the set can only be chosen once. Values are returned in ascending
/// order. Use random_shuffle() to randomize the sampled values.
/// @param population_size The total size of the population being sampled. The
/// maximum allowable value is UINT32_MAX + 1 (4294967296).
/// @param sample_size The number of samples being drawn from the set. The
/// maximum allowable value is UINT32_MAX + 1 (4294967296).
/// @param values Pointer to storage for an array of 32-bit unsigned integer
/// values that will be set to the sampled values. Values are stored in ascending order.
/// @param rng The state of the random number generator to be used when sampling the population.
void random_choose(uint64_t population_size, uint64_t sample_size, uint32_t *values, rng_state_t *rng);

/// @summary Samples a set with replacement. All values in the set have uniform
/// weight; that is, all values are equally likely to be chosen. Each value in
/// the set may be selected multiple times.
/// @param population_size The total size of the population being sampled. The
/// maximum allowable value is UINT32_MAX + 1 (4294967296).
/// @param sample_size The number of samples being drawn from the set. The
/// maximum allowable value is UINT32_MAX + 1 (4294967296).
/// @param values Pointer to storage for an array of 32-bit unsigned integer
/// values that will be set to the sampled values. Values are stored in ascending order.
/// @param rng The state of the random number generator to be used when sampling the population.
void random_choose_with_replacement(uint64_t population_size, uint64_t sample_size, uint32_t *values, rng_state_t *rng);

/// @summary Draws a single double-precision IEEE-754 floating point value from
/// a PRNG. Values are uniformly distributed over the range [0, 1).
/// @param rng The PRNG instance to draw from.
/// @return A value selected from the range [0, 1).
double random_draw(rng_state_t *rng);

/// @summary Draws a 32-bit unsigned integer value from a PRNG. Values are
/// uniformly distributed over the range [min_value, max_value). The caller
/// must ensure that min_value is less than max_value, and that the min and max
/// values are within the defined range, or the function may return invalid results.
/// @param min_value The inclusive lower-bound of the range. The maximum allowable value is UINT32_MAX + 1 (4294967296).
/// @param max_value The exclusive upper-bound of the range. The maximum allowable value is UINT32_MAX + 1 (4294967296).
/// @param rng The PRNG instance to draw from.
/// @return A value selected from the range [min_value, max_value).
uint32_t random_range(uint64_t min_value, uint64_t max_value, rng_state_t *rng);

/// @summary Retrieves 32 random bits from a PRNG. The bits are returned without
/// any transformation performed and the full range [0, UINT32_MAX] is possible.
/// @param rng The PRNG instance to draw from.
/// @return A value selected from the range [0, 4294967295].
uint32_t random_bits(rng_state_t *rng);

/// @summary Sets a 2-component vector or point value.
/// @param dst_xy Pointer to the destination storage.
/// @param x The x-component of the vector or point.
/// @param y The y-component of the vector or point.
/// @return The pointer dst_xy.
float* vec2_set_xy(float *dst_xy, float x, float y);

/// @summary Copies a 2-component vector or point value. The source and
/// destination values must not overlap.
/// @param dst_xy Pointer to the destination storage.
/// @param src_xy Pointer to the source value.
/// @return The pointer @a dst_xy.
float* vec2_set_vec2(float * __restrict dst_xy, float const * __restrict src_xy);

/// @summary Extracts the x- and y-components of a vector or point value into a
/// destination value. The source and destination values must not overlap.
/// @param dst_xy Pointer to the destination storage.
/// @param src_xyz Pointer to the source value.
/// @return The pointer dst_xy.
float* vec2_set_vec3(float * __restrict dst_xy, float const * __restrict src_xyz);

/// @summary Extracts the x- and y-components of a vector or point value into a
/// destination value. The source and destination values must not overlap.
/// @param dst_xy Pointer to the destination storage.
/// @param src_xyzw Pointer to the source value.
/// @return The pointer dst_xy.
float* vec2_set_vec4(float * __restrict dst_xy, float const * __restrict src_xyzw);

/// @summary Sets a 3-component vector or point value.
/// @param dst_xyz Pointer to the destination storage.
/// @param x The x-component of the vector or point.
/// @param y The y-component of the vector or point.
/// @param z The z-component of the vector or point.
/// @return The pointer dst_xyz.
float* vec3_set_xyz(float *dst_xyz, float x, float y, float z);

/// @summary Extracts the x- and y-components of a vector or point value into a
/// destination value with explicitly specified z-component. The source and
/// destination values must not overlap.
/// @param dst_xyz Pointer to the destination storage.
/// @param src_xy Pointer to the source storage from which the x- and y-components will be read.
/// @param z The z-component value.
/// @return The pointer to dst_xyz.
float* vec3_set_vec2(float * __restrict dst_xyz, float const * __restrict src_xy, float z);

/// @summary Copies a 3-component vector or point value. The source and
/// destination values must not overlap.
/// @param dst_xyz Pointer to the destination storage.
/// @param src_xyz Pointer to the source value.
/// @return The pointer dst_xyz.
float* vec3_set_vec3(float * __restrict dst_xyz, float const * __restrict src_xyz);

/// @summary Extracts the x- and y- and z-components of a vector or point value
/// into a destination value. The source and destination values must not overlap.
/// @param dst_xyz Pointer to the destination storage.
/// @param src_xyzw Pointer to the source storage from which the x- y- and z-components will be read.
/// @return The pointer to dst_xyz.
float* vec3_set_vec4(float * __restrict dst_xyz, float const * __restrict src_xyzw);

/// @summary Sets a 4-component vector or point value.
/// @param dst_xyzw Pointer to the destination storage.
/// @param x The x-component of the vector or point.
/// @param y The y-component of the vector or point.
/// @param z The z-component of the vector or point.
/// @param w The w-component of the vector or point. Vectors typically have a
/// w-component of zero; points typically have a w-component of one.
/// @return The pointer dst_xyzw.
float* vec4_set_xyzw(float *dst_xyzw, float x, float y, float z, float w);

/// @summary Extracts the x- and y-components of a vector or point value into a
/// destination value with explicitly specified z- and w-component. The source
/// and destination values must not overlap.
/// @param dst_xyz Pointer to the destination storage.
/// @param src_xy Pointer to the source storage from which the x- and y-components will be read.
/// @param z The z-component value.
/// @param w The w-component of the vector or point. Vectors typically have a
/// w-component of zero; points typically have a w-component of one.
/// @return The pointer dst_xyzw.
float* vec4_set_vec2(float * __restrict dst_xyzw, float const * __restrict src_xy, float z, float w);

/// @summary Extracts the x- y- and z-components of a vector or point value into
/// a destination value with explicitly specified w-component. The source and
/// destination values must not overlap.
/// @param dst_xyz Pointer to the destination storage.
/// @param src_xyz Pointer to the source storage from which the x- y- and z-components will be read.
/// @param w The w-component of the vector or point. Vectors typically have a
/// w-component of zero; points typically have a w-component of one.
/// @return The pointer dst_xyzw.
float* vec4_set_vec3(float * __restrict dst_xyzw, float const * __restrict src_xyz, float w);

/// @summary Copies a 4-component vector or point value. The source and destination values must not overlap.
/// @param dst_xyzw Pointer to the destination storage.
/// @param src_xyzw Pointer to the source value.
/// @return The pointer dst_xyzw.
float* vec4_set_vec4(float * __restrict dst_xyzw, float const * __restrict src_xyzw);

/// @summary Sets all elements of a vector to the IEEE-754 floating point Not-A-Number (NaN) value.
/// @param dst_xy Pointer to the destination storage.
/// @return The pointer dst_xy.
float* vec2_set_nan(float *dst_xy);

/// @summary Sets all elements of a vector to the IEEE-754 floating point Not-A-Number (NaN) value.
/// @param dst_xyz Pointer to the destination storage.
/// @return The pointer dst_xyz.
float* vec3_set_nan(float *dst_xyz);

/// @summary Sets all elements of a vector to the IEEE-754 floating point Not-A-Number (NaN) value.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_nan(float *dst_xyzw);

/// @summary Sets all elements of a vector to 1.0.
/// @param dst_xy Pointer to the destination storage.
/// @return The pointer dst_xy.
float* vec2_set_one(float *dst_xy);

/// @summary Sets all elements of a vector to 1.0.
/// @param dst_xyz Pointer to the destination storage.
/// @return The pointer dst_xyz.
float* vec3_set_one(float *dst_xyz);

/// @summary Sets all elements of a vector to 1.0.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_one(float *dst_xyzw);

/// @summary Sets all elements of a vector to 0.0.
/// @param dst_xy Pointer to the destination storage.
/// @return The pointer dst_xy.
float* vec2_set_zero(float *dst_xy);

/// @summary Sets all elements of a vector to 0.0.
/// @param dst_xyz Pointer to the destination storage.
/// @return The pointer dst_xyz.
float* vec3_set_zero(float *dst_xyz);

/// @summary Sets all elements of a vector to 0.0.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_zero(float *dst_xyzw);

/// @summary Sets all elements of a vector to the IEEE-754 floating point negative infinity value.
/// @param dst_xy Pointer to the destination storage.
/// @return The pointer dst_xy.
float* vec2_set_ninf(float *dst_xy);

/// @summary Sets all elements of a vector to the IEEE-754 floating point negative infinity value.
/// @param dst_xyz Pointer to the destination storage.
/// @return The pointer dst_xyz.
float* vec3_set_ninf(float *dst_xyz);

/// @summary Sets all elements of a vector to the IEEE-754 floating point negative infinity value.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_ninf(float *dst_xyzw);

/// @summary Sets all elements of a vector to the IEEE-754 floating point positive infinity value.
/// @param dst_xy Pointer to the destination storage.
/// @return The pointer dst_xy.
float* vec2_set_pinf(float *dst_xy);

/// @summary Sets all elements of a vector to the IEEE-754 floating point positive infinity value.
/// @param dst_xyz Pointer to the destination storage.
/// @return The pointer dst_xyz.
float* vec3_set_pinf(float *dst_xyz);

/// @summary Sets all elements of a vector to the IEEE-754 floating point positive infinity value.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_pinf(float *dst_xyzw);

/// @summary Sets the elements of a vector to the unit-length x-axis value <1,0>.
/// @param dst_xy Pointer to the destination storage.
/// @return The pointer dst_xy.
float* vec2_set_unit_x(float *dst_xy);

/// @summary Sets the elements of a vector to the unit-length x-axis value <1,0,0>.
/// @param dst_xyz Pointer to the destination storage.
/// @return The pointer dst_xyz.
float* vec3_set_unit_x(float *dst_xyz);

/// @summary Sets the elements of a vector to the unit-length x-axis value <1,0,0,0>.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_unit_x(float *dst_xyzw);

/// @summary Sets the elements of a vector to the unit-length y-axis value <0,1>.
/// @param dst_xy Pointer to the destination storage.
/// @return The pointer dst_xy.
float* vec2_set_unit_y(float *dst_xy);

/// @summary Sets the elements of a vector to the unit-length y-axis value <0,1,0>.
/// @param dst_xyz Pointer to the destination storage.
/// @return The pointer dst_xyz.
float* vec3_set_unit_y(float *dst_xyz);

/// @summary Sets the elements of a vector to the unit-length y-axis value <0,1,0,0>.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_unit_y(float *dst_xyzw);

/// @summary Sets the elements of a vector to the unit-length z-axis value <0,0,1>.
/// @param dst_xyz Pointer to the destination storage.
/// @return The pointer dst_xyz.
float* vec3_set_unit_z(float *dst_xyz);

/// @summary Sets the elements of a vector to the unit-length z-axis value <0,1,0,0>.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_unit_z(float *dst_xyzw);

/// @summary Sets the elements of a vector to the unit-length w-axis value <0,0,0,1>.
/// @param dst_xyzw Pointer to the destination storage.
/// @return The pointer dst_xyzw.
float* vec4_set_unit_w(float *dst_xyzw);

/// @summary Compares two vector values for equality.
/// @param a_xy The first vector value.
/// @param b_xy The second vector value.
/// @return true if a_xy and b_xy can be considered equal.
bool vec2_eq(float const * __restrict a_xy, float const * __restrict b_xy);

/// @summary Compares two vector values for equality.
/// @param a_xyz The first vector value.
/// @param b_xyz The second vector value.
/// @return true if a_xyz and b_xyz can be considered equal.
bool vec3_eq(float const * __restrict a_xyz, float const * __restrict b_xyz);

/// @summary Compares two vector values for equality.
/// @param a_xyzw The first vector value.
/// @param b_xyzw The second vector value.
/// @return true if a_xyzw and b_xyzw can be considered equal.
bool vec4_eq(float const * __restrict a_xyzw, float const * __restrict b_xyzw);

/// @summary Performs component-wise addition of two vector quantities, storing
/// the result in a third, such that dst = a + b.
/// @param dst_xy Pointer to the destination storage.
/// @param a_xy The first source value.
/// @param b_xy The second source value.
/// @return The pointer dst_xy.
float* vec2_add(float * __restrict dst_xy, float const * __restrict a_xy, float const * __restrict b_xy);

/// @summary Performs component-wise addition of two vector quantities, storing
/// the result in a third, such that dst = a + b.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The first source value.
/// @param b_xyz The second source value.
/// @return The pointer dst_xyz.
float* vec3_add(float * __restrict dst_xyz, float const * __restrict a_xyz, float const * __restrict b_xyz);

/// @summary Performs component-wise addition of two vector quantities, storing
/// the result in a third, such that dst = a + b.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The first source value.
/// @param b_xyzw The second source value.
/// @return The pointer dst_xyzw.
float* vec4_add(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);

/// @summary Performs component-wise subtraction of two vector quantities,
/// storing the result in a third, such that dst = a - b.
/// @param dst_xy Pointer to the destination storage.
/// @param a_xy The first source value.
/// @param b_xy The second source value.
/// @return The pointer dst_xy.
float* vec2_sub(float * __restrict dst_xy, float const * __restrict a_xy, float const * __restrict b_xy);

/// @summary Performs component-wise subtraction of two vector quantities,
/// storing the result in a third, such that dst = a - b.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The first source value.
/// @param b_xyz The second source value.
/// @return The pointer dst_xyz.
float* vec3_sub(float * __restrict dst_xyz, float const * __restrict a_xyz, float const * __restrict b_xyz);

/// @summary Performs component-wise subtraction of two vector quantities,
/// storing the result in a third, such that dst = a - b.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The first source value.
/// @param b_xyzw The second source value.
/// @return The pointer dst_xyzw.
float* vec4_sub(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);

/// @summary Performs component-wise multiplication of two vector quantities,
/// storing the result in a third, such that dst = a * b.
/// @param dst_xy Pointer to the destination storage.
/// @param a_xy The first source value.
/// @param b_xy The second source value.
/// @return The pointer to dst_xy.
float* vec2_mul(float * __restrict dst_xy, float const * __restrict a_xy, float const * __restrict b_xy);

/// @summary Performs component-wise multiplication of two vector quantities,
/// storing the result in a third, such that dst = a * b.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The first source value.
/// @param b_xyz The second source value.
/// @return The pointer to dst_xyz.
float* vec3_mul(float * __restrict dst_xyz, float const * __restrict a_xyz, float const * __restrict b_xyz);

/// @summary Performs component-wise multiplication of two vector quantities,
/// storing the result in a third, such that dst = a * b.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The first source value.
/// @param b_xyzw The second source value.
/// @return The pointer to dst_xyzw.
float* vec4_mul(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);

/// @summary Performs component-wise division of two vector quantities, storing
/// the result in a third, such that dst = a / b.
/// @param dst_xy Pointer to the destination storage.
/// @param a_xy The first source value.
/// @param b_xy The second source value.
/// @return The pointer to dst_xy.
float* vec2_div(float * __restrict dst_xy, float const * __restrict a_xy, float const * __restrict b_xy);

/// @summary Performs component-wise division of two vector quantities, storing
/// the result in a third, such that dst = a / b.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The first source value.
/// @param b_xyz The second source value.
/// @return The pointer to @a dst_xyz.
float* vec3_div(float * __restrict dst_xyz, float const * __restrict a_xyz, float const * __restrict b_xyz);

/// @summary Performs component-wise division of two vector quantities, storing
/// the result in a third, such that dst = a / b.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The first source value.
/// @param b_xyzw The second source value.
/// @return The pointer to dst_xyzw.
float* vec4_div(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);

/// @summary Multiplies each component of a vector value by a scalar.
/// @param dst_xy Pointer to the destination storage.
/// @param a_xy The source vector value.
/// @param b The scalar value.
/// @return The pointer to dst_xy.
float* vec2_scl(float * __restrict dst_xy, float const * __restrict a_xy, float b);

/// @summary Multiplies each component of a vector value by a scalar.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The source vector value.
/// @param b The scalar value.
/// @return The pointer to dst_xyz.
float* vec3_scl(float * __restrict dst_xyz, float const * __restrict a_xyz, float b);

/// @summary Multiplies each component of a vector value by a scalar.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The source vector value.
/// @param b The scalar value.
/// @return The pointer to dst_xyzw.
float* vec4_scl(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float b);

/// @summary Multiplies each component of a vector value by a scalar. Only the
/// first three components of the vector are multiplied by the scalar value.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The source vector value.
/// @param b The scalar value.
/// @return The pointer to dst_xyzw.
float* vec4_scl3(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float b);

/// @summary Negates each component of a vector value, preserving the magnitude
/// but reversing the direction.
/// @param dst_xy Pointer to the destination storage.
/// @param src_xy The source vector value.
/// @return The pointer to dst_xy.
float* vec2_neg(float * __restrict dst_xy, float const * __restrict src_xy);

/// @summary Negates each component of a vector value, preserving the magnitude
/// but reversing the direction.
/// @param dst_xyz Pointer to the destination storage.
/// @param src_xyz The source vector value.
/// @return The pointer to dst_xyz.
float* vec3_neg(float * __restrict dst_xyz, float const * __restrict src_xyz);

/// @summary Negates each component of a vector value, preserving the magnitude
/// but reversing the direction.
/// @param dst_xyzw Pointer to the destination storage.
/// @param src_xyzw The source vector value.
/// @return The pointer to dst_xyzw.
float* vec4_neg(float * __restrict dst_xyzw, float const * __restrict src_xyzw);

/// @summary Negates each component of a vector value, preserving the magnitude
/// but reversing the direction. Only the first three components are negated.
/// @param dst_xyzw Pointer to the destination storage.
/// @param src_xyzw The source vector value.
/// @return The pointer to dst_xyzw.
float* vec4_neg3(float * __restrict dst_xyzw, float const * __restrict src_xyzw);

/// @summary Computes the dot product of two vectors.
/// @param dst On return, this value is set to the dot product of a and b.
/// @param a_xy Vector value a.
/// @param b_xy Vector value b.
/// @return The dot product of the vectors.
float vec2_dot(float &dst, float const * __restrict a_xy, float const * __restrict b_xy);

/// @summary Computes the dot product of two vectors.
/// @param dst On return, this value is set to the dot product of a and b.
/// @param a_xyz Vector value a.
/// @param b_xyz Vector value b.
/// @return The dot product of the vectors.
float vec3_dot(float &dst, float const * __restrict a_xyz, float const * __restrict b_xyz);

/// @summary Computes the dot product of two vectors.
/// @param dst On return, this value is set to the dot product of a and b.
/// @param a_xyzw Vector value a.
/// @param b_xyzw Vector value b.
/// @return The dot product of the vectors.
float vec4_dot(float &dst, float const * __restrict a_xyzw, float const * __restrict b_xyzw);

/// @summary Computes the dot product of two vectors, considering only the first three components of each.
/// @param dst On return, this value is set to the dot product of a and b.
/// @param a_xyzw Vector value a.
/// @param b_xyzw Vector value b.
/// @return The dot product of the vectors.
float vec4_dot3(float &dst, float const * __restrict a_xyzw, float const * __restrict b_xyzw);

/// @summary Calculates the magnitude (length) of a vector.
/// @param dst On return, this value is set to the length of the vector.
/// @param a_xy The vector value.
/// @return The magnitude (length) of vector a_xy.
float vec2_len(float &dst, float const *a_xy);

/// @summary Calculates the magnitude (length) of a vector.
/// @param dst On return, this value is set to the length of the vector.
/// @param a_xyz The vector value.
/// @return The magnitude (length) of vector a_xyz.
float vec3_len(float &dst, float const *a_xyz);

/// @summary Calculates the magnitude (length) of a vector.
/// @param dst On return, this value is set to the length of the vector.
/// @param a_xyzw The vector value.
/// @return The magnitude (length) of vector a_xyzw.
float vec4_len(float &dst, float const *a_xyzw);

/// @summary Calculates the magnitude (length) of a vector. Only the first
/// three components of the vector are considered.
/// @param dst On return, this value is set to the length of the vector.
/// @param a_xyzw The vector value.
/// @return The magnitude (length) of vector a_xyzw.
float vec4_len3(float &dst, float const *a_xyzw);

/// @summary Calculates the squared magnitude (length) of a vector.
/// @param dst On return, this value is set to the squared length of the vector.
/// @param a_xy The vector value.
/// @return The squared magnitude (length) of vector a_xy.
float vec2_len_sq(float &dst, float const *a_xy);

/// @summary Calculates the squared magnitude (length) of a vector.
/// @param dst On return, this value is set to the squared length of the vector.
/// @param a_xyz The vector value.
/// @return The squared magnitude (length) of vector a_xyz.
float vec3_len_sq(float &dst, float const *a_xyz);

/// @summary Calculates the squared magnitude (length) of a vector.
/// @param dst On return, this value is set to the squared length of the vector.
/// @param a_xyzw The vector value.
/// @return The squared magnitude (length) of vector a_xyzw.
float vec4_len_sq(float &dst, float const *a_xyzw);

/// @summary Calculates the squared magnitude (length) of a vector.
/// @param dst On return, this value is set to the squared length of the vector.
/// @param a_xy The vector value.
/// @return The squared magnitude (length) of vector a_xy.
float vec4_len3_sq(float &dst, float const *a_xyzw);

/// @summary Calculates the normalized (unit-length) vector for a given vector
/// value. The normalized vector has the same direction, but magnitude 1.
/// @param dst_xy Pointer to the destination storage.
/// @param src_xy The source vector value.
/// @return The pointer dst_xy.
float* vec2_nrm(float * __restrict dst_xy, float const * __restrict src_xy);

/// @summary Calculates the normalized (unit-length) vector for a given vector
/// value. The normalized vector has the same direction, but magnitude 1.
/// @param dst_xyz Pointer to the destination storage.
/// @param src_xyz The source vector value.
/// @return The pointer dst_xyz.
float* vec3_nrm(float * __restrict dst_xyz, float const * __restrict src_xyz);

/// @summary Calculates the normalized (unit-length) vector for a given vector
/// value. The normalized vector has the same direction, but magnitude 1.
/// @param dst_xyzw Pointer to the destination storage.
/// @param src_xyzw The source vector value.
/// @return The pointer dst_xyzw.
float* vec4_nrm(float * __restrict dst_xyzw, float const * __restrict src_xyzw);

/// @summary Calculates the normalized (unit-length) vector for a given vector
/// value. The normalized vector has the same direction, but magnitude 1. Only
/// the first three components of src_xyzw are considered when computing the
/// length and normalizing the vector.
/// @param dst_xyzw Pointer to the destination storage.
/// @param src_xyzw The source vector value.
/// @return The pointer dst_xyzw.
float* vec4_nrm3(float * __restrict dst_xyzw, float const * __restrict src_xyzw);

/// @summary Calculates a vector perpendicular to a given vector, but with the same magnitude.
/// @param dst_xy Pointer to the destination storage.
/// @param src_xy The source vector value.
/// @return The pointer dst_xy.
float* vec2_perp(float * __restrict dst_xy, float const * __restrict src_xy);

/// @summary Calculates the cross product of two vectors, producing a third
/// vector that is orthogonal to the source vectors; the dot product of the
/// resulting vector with either of the source vectors is zero.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The first source vector.
/// @param b_xyz The second source vector.
/// @return The pointer dst_xyz.
float* vec3_cross(float * __restrict dst_xyz, float const * __restrict a_xyz, float const * __restrict b_xyz);

/// @summary Calculates the cross product of two vectors, producing a third
/// vector that is orthogonal to the source vectors; the dot product of the
/// resulting vector with either of the source vectors is zero. The w-component
/// of the resulting vector is always zero, since the cross product operation
/// always results in a vector value.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The first source vector.
/// @param b_xyzw The second source vector.
/// @return The pointer dst_xyzw.
float* vec4_cross(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);

/// @summary Performs a swizzle operation on a vector or point value to select
/// or change the order of components.
/// @param dst_xy Pointer to the destination storage.
/// @param src_xy The source value.
/// @param x The zero-based index of the source component that will be written
/// to the destination value at index 0.
/// @param y The zero-based index of the source component that will be written
/// to the destination value at index 1.
/// @return The pointer dst_xy.
float* vec2_swizzle(float * __restrict dst_xy, float const * __restrict src_xy, size_t x, size_t y);

/// @summary Performs a swizzle operation on a vector or point value to select
/// or change the order of components.
/// @param dst_xyz Pointer to the destination storage.
/// @param src_xyz The source value.
/// @param x The zero-based index of the source component that will be written
/// to the destination value at index 0.
/// @param y The zero-based index of the source component that will be written
/// to the destination value at index 1.
/// @param z The zero-based index of the source component that will be written
/// to the destination value at index 2.
/// @return The pointer dst_xyz.
float* vec3_swizzle(float * __restrict dst_xyz, float const * __restrict src_xyz, size_t x, size_t y, size_t z);

/// @summary Performs a swizzle operation on a vector or point value to select
/// or change the order of components.
/// @param dst_xyzw Pointer to the destination storage.
/// @param src_xyzw The source value.
/// @param x The zero-based index of the source component that will be written
/// to the destination value at index 0.
/// @param y The zero-based index of the source component that will be written
/// to the destination value at index 1.
/// @param z The zero-based index of the source component that will be written
/// to the destination value at index 2.
/// @param w The zero-based index of the source component that will be written
/// to the destination value at index 3.
/// @return The pointer dst_xyzw.
float* vec4_swizzle(float * __restrict dst_xyzw, float const * __restrict src_xyzw, size_t x, size_t y, size_t z, size_t w);

/// @summary Performs componentwise linear interpolation between two vector or point quantities.
/// @param dst_xy Pointer to the destination storage.
/// @param a_xy The value at @a t = 0.
/// @param b_xy The value at @a t = 1.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xy.
float* vec2_linear(float * __restrict dst_xy, float const * __restrict a_xy, float const * __restrict b_xy, float t);

/// @summary Performs componentwise linear interpolation between two vector or point quantities.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The value at @a t = 0.
/// @param b_xyz The value at @a t = 1.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyz.
float* vec3_linear(float * __restrict dst_xyz, float const * __restrict a_xyz, float const * __restrict b_xyz, float t);

/// @summary Performs componentwise linear interpolation between two vector or point quantities.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The value at @a t = 0.
/// @param b_xyzw The value at @a t = 1.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyzw.
float* vec4_linear(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw, float t);

/// @summary Performs componentwise linear interpolation between two vector or
/// point quantities. Only the first three components are interpolated.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The value at @a t = 0.
/// @param b_xyzw The value at @a t = 1.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyzw.
float* vec4_linear3(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw, float t);

/// @summary Performs componentwise Bezier interpolation between two vector or point quantities.
/// @param dst_xy Pointer to the destination storage.
/// @param a_xy The value at @a t = 0.
/// @param b_xy The value at @a t = 1.
/// @param itan_xy The incoming tangent value.
/// @param otan_xy The outgoing tangent value.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xy.
float* vec2_bezier(
    float       * __restrict dst_xy,
    float const * __restrict a_xy,
    float const * __restrict b_xy,
    float const * __restrict itan_xy,
    float const * __restrict otan_xy,
    float                  t);

/// @summary Performs componentwise Bezier interpolation between two vector or point quantities.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The value at @a t = 0.
/// @param b_xyz The value at @a t = 1.
/// @param itan_xyz The incoming tangent value.
/// @param otan_xyz The outgoing tangent value.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyz.
float* vec3_bezier(
    float       * __restrict dst_xyz,
    float const * __restrict a_xyz,
    float const * __restrict b_xyz,
    float const * __restrict itan_xyz,
    float const * __restrict otan_xyz,
    float                  t);

/// @summary Performs componentwise Bezier interpolation between two vector or point quantities.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The value at @a t = 0.
/// @param b_xyzw The value at @a t = 1.
/// @param itan_xyzw The incoming tangent value.
/// @param otan_xyzw The outgoing tangent value.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyzw.
float* vec4_bezier(
    float       * __restrict dst_xyzw,
    float const * __restrict a_xyzw,
    float const * __restrict b_xyzw,
    float const * __restrict itan_xyzw,
    float const * __restrict otan_xyzw,
    float                  t);

/// @summary Performs componentwise Bezier interpolation between two vector or
/// point quantities. Only the first three components are interpolated.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The value at @a t = 0.
/// @param b_xyzw The value at @a t = 1.
/// @param itan_xyzw The incoming tangent value.
/// @param otan_xyzw The outgoing tangent value.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyzw.
float* vec4_bezier3(
    float       * __restrict dst_xyzw,
    float const * __restrict a_xyzw,
    float const * __restrict b_xyzw,
    float const * __restrict itan_xyz,
    float const * __restrict otan_xyz,
    float                  t);

/// @summary Performs componentwise Hermite interpolation between two vector or point quantities.
/// @param dst_xy Pointer to the destination storage.
/// @param a_xy The value at @a t = 0.
/// @param b_xy The value at @a t = 1.
/// @param itan_xy The incoming tangent value.
/// @param otan_xy The outgoing tangent value.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xy.
float* vec2_hermite(
    float       * __restrict dst_xy,
    float const * __restrict a_xy,
    float const * __restrict b_xy,
    float const * __restrict itan_xy,
    float const * __restrict otan_xy,
    float                  t);

/// @summary Performs componentwise Hermite interpolation between two vector or point quantities.
/// @param dst_xyz Pointer to the destination storage.
/// @param a_xyz The value at @a t = 0.
/// @param b_xyz The value at @a t = 1.
/// @param itan_xyz The incoming tangent value.
/// @param otan_xyz The outgoing tangent value.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyz.
float* vec3_hermite(
    float       * __restrict dst_xyz,
    float const * __restrict a_xyz,
    float const * __restrict b_xyz,
    float const * __restrict itan_xyz,
    float const * __restrict otan_xyz,
    float                  t);

/// @summary Performs componentwise Hermite interpolation between two vector or point quantities.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The value at @a t = 0.
/// @param b_xyzw The value at @a t = 1.
/// @param itan_xyzw The incoming tangent value.
/// @param otan_xyzw The outgoing tangent value.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyzw.
float* vec4_hermite(
    float       * __restrict dst_xyzw,
    float const * __restrict a_xyzw,
    float const * __restrict b_xyzw,
    float const * __restrict itan_xyzw,
    float const * __restrict otan_xyzw,
    float                      t);

/// @summary Performs componentwise Hermite interpolation between two vector or
/// point quantities. Only the first three components are interpolated.
/// @param dst_xyzw Pointer to the destination storage.
/// @param a_xyzw The value at @a t = 0.
/// @param b_xyzw The value at @a t = 1.
/// @param itan_xyz The incoming tangent value.
/// @param otan_xyz The outgoing tangent value.
/// @param t A value in the range [0, 1] specifying the interpolation parameter.
/// @return The pointer dst_xyzw.
float* vec4_hermite3(
    float       * __restrict dst_xyzw,
    float const * __restrict a_xyzw,
    float const * __restrict b_xyzw,
    float const * __restrict itan_xyz,
    float const * __restrict otan_xyz,
    float                  t);

float* quat_set_xyzw(float *dst_xyzw, float x, float y, float z, float w);
float* quat_set_quat(float * __restrict dst_xyzw, float const * __restrict src_xyzw);
float* quat_set_nan(float *dst_xyzw);
float* quat_set_one(float *dst_xyzw);
float* quat_set_zero(float *dst_xyzw);
float* quat_set_ninf(float *dst_xyzw);
float* quat_set_pinf(float *dst_xyzw);
float* quat_set_ident(float *dst_xyzw);
bool   quat_eq(float const * __restrict a_xyzw, float const * __restrict b_xyzw);
float* quat_add(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);
float* quat_sub(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);
float* quat_mul(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);
float* quat_scl(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float b);
float* quat_scl3(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float b);
float* quat_neg(float * __restrict dst_xyzw, float const * __restrict src_xyzw);
float* quat_neg3(float * __restrict dst_xyzw, float const * __restrict src_xyzw);
float* quat_conj(float * __restrict dst_xyzw, float const * __restrict src_xyzw);
float  quat_dot(float const * __restrict a_xyzw, float const * __restrict b_xyzw);
float  quat_norm(float const *src_xyzw);
float  quat_len(float const *src_xyzw);
float  quat_len_sq(float const *src_xyzw);
float  quat_sel(float const *src_xyzw);
float* quat_inv(float * __restrict dst_xyzw, float const * __restrict src_xyzw);
float* quat_nrm(float * __restrict dst_xyzw, float const * __restrict src_xyzw);
float* quat_exp(float * __restrict dst_xyzw, float const * __restrict src_xyzw);
float* quat_log(float * __restrict dst_xyzw, float const * __restrict src_xyzw);
float* quat_closest(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw);
float* quat_orient_vec3(float *__restrict dst_xyzw, float const * __restrict from_xyz, float const * __restrict to_xyz);
float* quat_orient_vec4(float * __restrict dst_xyzw, float const * __restrict from_xyzw, float const * __restrict to_xyzw);
float* quat_set_mat4(float * __restrict dst_xyzw, float const * __restrict m16);
float* quat_set_euler_degree(float * __restrict dst_xyzw, float deg_x, float deg_y, float deg_z);
float* quat_set_euler_radian(float * __restrict dst_xyzw, float rad_x, float rad_y, float rad_z);
float* quat_set_angle_axis_degree_n(float * __restrict dst_xyzw, float angle_deg, float const * __restrict axis_xyz);
float* quat_set_angle_axis_radian_n(float * __restrict dst_xyzw, float angle_rad, float const * __restrict axis_xyz);
float* quat_set_angle_axis_degree_u(float * __restrict dst_xyzw, float angle_deg, float const * __restrict axis_xyz);
float* quat_set_angle_axis_radian_u(float * __restrict dst_xyzw, float angle_rad, float const * __restrict axis_xyz);
float* quat_linear(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw, float t);
float* quat_slerp(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw, float t);
float* quat_squad(float * __restrict dst_xyzw, float const * __restrict p_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw, float const * __restrict q_xyzw, float t);
float* quat_spline(float * __restrict dst_xyzw, float const * __restrict a_xyzw, float const * __restrict b_xyzw, float const * __restrict c_xyzw);

float* mat4_set(float *dst16, float  r0c0, float r0c1, float r0c2, float r0c3, float  r1c0, float r1c1, float r1c2, float r1c3, float  r2c0, float r2c1, float r2c2, float r2c3, float  r3c0, float r3c1, float r3c2, float r3c3);
float* mat4_set_mat4(float * __restrict dst16, float const * __restrict src16);
float* mat4_set_nan(float *dst16);
float* mat4_set_one(float *dst16);
float* mat4_set_zero(float *dst16);
float* mat4_set_ninf(float *dst16);
float* mat4_set_pinf(float *dst16);
float* mat4_set_ident(float *dst16);
bool   mat4_eq(float const * __restrict a16, float const * __restrict b16);
bool   mat4_is_identity(float const *src16);
float* mat4_set_rows(float * __restrict dst16, float const * __restrict r0_xyzw, float const * __restrict r1_xyzw, float const * __restrict r2_xyzw, float const * __restrict r3_xyzw);
float* mat4_set_cols(float * __restrict dst16, float const * __restrict c0_xyzw, float const * __restrict c1_xyzw, float const * __restrict c2_xyzw, float const * __restrict c3_xyzw);
float* mat4_get_row(float * __restrict dst_xyzw, size_t row, float const *__restrict src16);
float* mat4_set_row(float * __restrict dst16, size_t row, float const *__restrict src_xyzw);
float* mat4_get_col(float * __restrict dst_xyzw, size_t col, float const *__restrict src16);
float* mat4_set_col(float * __restrict dst16, size_t col, float const * __restrict src_xyzw);
float  mat4_trace(float const *src16);
float  mat4_det(float const *src16);
float* mat4_transpose(float * __restrict dst16, float const * __restrict src16);
float* mat4_concat(float * __restrict dst16, float const * __restrict a16, float const * __restrict b16);
float* mat4_inv_affine(float * __restrict dst16, float const * __restrict src16);
float* mat4_set_quat(float * __restrict dst16, float const * __restrict src_xyzw);
float* mat4_set_euler_degree_x(float *dst16, float deg_x);
float* mat4_set_euler_radian_x(float *dst16, float rad_x);
float* mat4_set_euler_degree_y(float *dst16, float deg_y);
float* mat4_set_euler_radian_y(float *dst16, float rad_y);
float* mat4_set_euler_degree_z(float *dst16, float deg_z);
float* mat4_set_euler_radian_z(float *dst16, float rad_z);
float* mat4_set_euler_degree(float *dst16, float deg_x, float deg_y, float deg_z);
float* mat4_set_euler_radian(float *dst16, float rad_x, float rad_y, float rad_z);
float* mat4_set_angle_axis_degree_n(float * __restrict dst16, float angle_deg, float const * __restrict axis_xyz);
float* mat4_set_angle_axis_radian_n(float * __restrict dst16, float angle_rad, float const * __restrict axis_xyz);
float* mat4_set_angle_axis_degree_u(float * __restrict dst16, float angle_deg, float const * __restrict axis_xyz);
float* mat4_set_angle_axis_radian_u(float * __restrict dst16, float angle_rad, float const * __restrict axis_xyz);
float* mat4_look_at(float * __restrict dst16, float const * __restrict pos_xyz, float const * __restrict target_xyz, float const * __restrict up_xyz);
float* mat4_scale(float *dst16, float scale_x, float scale_y, float scale_z);
float* mat4_trans(float *dst16, float trans_x, float trans_y, float trans_z);
float* mat4_ortho(float *dst16, float left, float right, float bottom, float top, float near, float far);
float* mat4_persp_degree(float *dst16, float fov_deg, float aspect, float near, float far);
float* mat4_persp_radian(float *dst16, float fov_rad, float aspect, float near, float far);
float* mat4_2d(float *dst16, float width, float height);
void   mat4_extract_frustum_n(float * __restrict left_xyzD, float * __restrict right_xyzD, float * __restrict top_xyzD, float * __restrict bottom_xyzD, float * __restrict near_xyzD, float * __restrict far_xyzD, float const * __restrict proj16);
void   mat4_extract_frustum_u(float * __restrict left_xyzD, float * __restrict right_xyzD, float * __restrict top_xyzD, float * __restrict bottom_xyzD, float * __restrict near_xyzD, float * __restrict far_xyzD, float const * __restrict proj16);
float* mat4_transform_vec3(float * __restrict dst_xyz, float const * __restrict src_xyz, float const * __restrict t16);
float* mat4_transform_vec4(float * __restrict dst_xyzw, float const * __restrict src_xyzw, float const * __restrict t16);
float* mat4_transform_point(float * __restrict dst_xyz, float const * __restrict src_xyz, float const * __restrict t16);
float* mat4_transform_vector(float * __restrict dst_xyz, float const * __restrict src_xyz, float const * __restrict t16);
float* mat4_transform_array_vec3(float * __restrict dst_xyz, float const * __restrict src_xyz, float const * __restrict t16, size_t count);
float* mat4_transform_array_vec4(float * __restrict dst_xyzw, float const * __restrict src_xyzw, float const * __restrict t16, size_t count);
float* mat4_transform_array_point(float * __restrict dst_xyz, float const * __restrict src_xyz, float const * __restrict t16, size_t count);
float* mat4_transform_array_vector(float * __restrict dst_xyz, float const * __restrict src_xyz, float const * __restrict t16, size_t count);

/// Determine the smallest representable value for a given integer type.
/// @return The smallest representable value for a given integer type.
template <typename T>
inline T int_type_min(void)
{
    return std::numeric_limits<T>::min();
}

/// Determine the largest representable value for a given integer type.
/// @return The largest representable value for a given integer type.
template <typename T>
inline T int_type_max(void)
{
    return std::numeric_limits<T>::max();
}

/// Assign the sum of @a a and @a b to @a dst if the assignment would be
/// allowed based on type, and no loss of precision would occur.
/// @param dst The address of the value to update.
/// @param a The left-hand addend.
/// @param b The right-hand addend.
/// @return true if the addition and assignment operation would have resulted
/// in a loss of precision based on the source and destination types.
template <typename X, typename Y, typename Z>
inline bool int_assign_add(X &dst, Y const a, Z const b)
{
    Y __x = a+b; // compiler sum w/conversions
    X __y = __x; // copy of result stored in dest. type
    return (__x == __y && ((__x < 1) == (__y < 1)) ? (void)(dst = __y), false : true);
}

/// Assign the difference of @a a and @a b to @a dst if the assignment would be
/// allowed based on type, and if no loss of precision would occur.
/// @param dst The address of the value to update.
/// @param a The minuend.
/// @param b The subtrahend.
/// @return true if the subtraction and assignment operation would have
/// resulted in a loss of precision based on source and destination types.
template <typename X, typename Y, typename Z>
inline bool int_assign_sub(X &dst, Y const a, Z const b)
{
    Y __x = a-b; // compiler difference w/conversions
    X __y = __x; // copy of result stored in dest. type
    return (__x == __y && ((__x < 1) == (__y < 1)) ? (void)(dst = __y), false : true);
}

/// Assign the sum of @a a and @a b to @a dst if and only if the assignment
/// would be allowed based on type, with no loss of precision or overflow.
/// @param dst The address of the value to update.
/// @param a The left-hand addend.
/// @param b The right-hand addend.
/// @return true if the addition and assignment operation would have resulted
/// in a loss of precision, overflow or underflow based on the source and
/// destination types.
template <typename X, typename Y, typename Z>
inline bool int_add(X &dst, Y const a, Z const b)
{
    Y __a = a;
    Z __b = b;
    return (__b < 1) ?
        ((int_type_min<X>() - (__b) <= (__a)) ? int_assign_add(dst, __a, __b) : true) :
        ((int_type_max<X>() - (__b) >= (__a)) ? int_assign_add(dst, __a, __b) : true) ;
}

/// Assign the difference of @a a and @a b to @a dst if and only if the
/// assignment would be allowed based on type, with no loss of precision or
/// overflow.
/// @param dst The address of the value to update.
/// @param a The minuend.
/// @param b The subtrahend.
/// @return true if the subtraction and assignment operation would have
/// resulted in a loss of precision, overflow or underflow based on the source
/// and destination types.
template <typename X, typename Y, typename Z>
inline bool int_sub(X &dst, Y const a, Z const b)
{
    Y __a = a;
    Z __b = b;
    return (__b < 1) ?
        ((int_type_max<X>() + (__b) >= (__a)) ? int_assign_sub(dst, __a, __b) : true) :
        ((int_type_min<X>() + (__b) <= (__a)) ? int_assign_sub(dst, __a, __b) : true) ;
}

#endif /* !defined(GW_MATH_HPP) */
