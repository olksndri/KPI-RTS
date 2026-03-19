#include <iostream>
#include <vector>
#include <random>
#include <chrono> 

// Display matrix
void display_matrix(float *mtx, int M, int N) 
{

	printf("matrix %dx%d: \n", M, N); 
	for(int m = 0; m < M; m++)
		for(int n = 0; n < N; n++)
		{
			int idx = m * N + n; 
			printf("%.2f ", mtx[idx]);
			if((idx + 1) % N == 0) 
				printf("\n");
		}
	printf("\n"); 
}

// Display vector 
void display_vector(float *vec, int vec_len) 
{ 
	printf("vector %dx1: \n", vec_len); 
	for(int x = 0; x < vec_len; x++)
		printf("%.2f\n", vec[x]);
	printf("\n"); 
}

// Fill vector with random float values in range [min, max)  
void fill_random_vector(std::vector<float>& X, float min, float max)
{
	std::random_device rd; 
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(min, max);

	for(float &Xn : X)
		Xn = dist(mt); 
}

/*  Matrix multiply by vector function 
	@param	vec_out		result vector 
	@param	mtx			input matrix 
	@param	vec			input vector 
	@param	M			rows of matrix 
	@param	N			columns of matrix and rows of vector
*/
void matrix_mul_vector(	std::vector<float>& vec_out,
						const std::vector<float>& mtx, const std::vector<float>& vec, 	
						int M, int N )
{
	for(int m = 0; m < M; m++) // Iterate through matrix rows 
	{
		float acc = 0;  
		
		for(int n = 0; n < N; n++) // Iterate through matrix columns and vector rows 
			acc += mtx[m * N + n] * vec[n]; 		
		
		vec_out[m] = acc; 
	}
}


int main(int, char**)
{
	int M = 10; 
	int N = 10; 
	int mtx_size = M * N; 
	int vec_size = N * 1; 
	int vec_out_size = M * 1; 

	std::vector<float> mtx(mtx_size); 
	std::vector<float> vec(vec_size); 
	std::vector<float> vec_out(vec_out_size); 

	fill_random_vector(mtx, 0, 1.0f); 
	fill_random_vector(vec, 0, 10.0f); 

	if(M < 25 || N < 25)
	{
		display_matrix(mtx.data(), M, N);  
		display_vector(vec.data(), vec_size);
	} 

	std::cout << "_______________________ \n\n"; 
	std::cout << "matrix size MxN " << M << "x" << N << "\n"; 
	std::cout << "vector size Nx1 " << N << "x" << 1 << "\n"; 

	auto t0 = std::chrono::steady_clock::now(); 
	matrix_mul_vector(vec_out, mtx, vec, M, N);
	auto t1 = std::chrono::steady_clock::now(); 
	auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0); 

	if(M < 25 || N < 25)
		display_vector(vec_out.data(), vec_out_size);  

    std::cout << "matrix_mul_vector() time elapsed: " << duration.count() << " microseconds\n"; 

	return 0; 
}
