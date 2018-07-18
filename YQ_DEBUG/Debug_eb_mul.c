in test_yiqun.c: multiplication()
Line 678:
			bn_rand_mod(k, n);
			eb_mul(q, p, k);

(gdb) p/x k
$18 = {{alloc = 0x22, used = 0x5, sign = 0x0, dp = {0x54d98527a61946a9, 0x4550b3557a250d65, 0x2464d1aad631c046, 0x1c89aaeb8b15a787, 0xc73b8, 0x0 <repeats 29 times>}}}

(gdb) p/x p
$19 = {{x = {0x3cd1073a2a3cece3, 0xcebf5cbe5f6aa9ef, 0x44dfa2cd5e04d7c1, 0xfba64538bec64324, 0x51624c9}, y = {0xd99e33e72804c43b, 0x3f12af24dcbf245b, 0x1afccb09db122d7d, 
      0x98239a3559e5a9a, 0x6d58530}, z = {0x1, 0x0, 0x0, 0x0, 0x0}, norm = 0x1}}

(gdb) p/x q
$20 = {{x = {0x6e90ff2c5bbd77fc, 0xbfb5dd29eb6191b0, 0x374d2e71befe2535, 0x5b52096d8a97985f, 0xbd087}, y = {0x432aa420a6c21788, 0x92a04714dd7e6d46, 0x1a3791442d5a6f44, 0xcac1df50bf7f057f, 
      0x61cc432}, z = {0x1, 0x0, 0x0, 0x0, 0x0}, norm = 0x1}}

eb_mul(q,p,k) {
	
	eb_mul_lwnaf(eb_t r, const eb_t p, const bn_t k) {

	 	eb_mul_lnaf_imp(eb_t r, const eb_t p, const bn_t k) {
			
			bn_rec_naf();

			some eb_add, eb_sub;


		}

	}

}

Results from dve:

36757d3e
f92979f6
9908df3c
f368cfd4
eb260c21
38f51d08
2742a865
c22d4326
eca9f0a0
c5669560
2cb53350
6f472677
6d5b7e85
602e346f
ca2cd695
2486458b
04b554ed
