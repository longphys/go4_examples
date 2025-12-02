{

	*(memory.p32++) = (long)0x2000000L + (long)((30 & 0x1f) << 27);
	gettimeofday(&vt_tx, NULL);
	*(memory.p32++) = (vt_tx.tv_sec - vt_t0.tv_sec)*1000 + (vt_tx.tv_usec - vt_t0.tv_usec)/1000;
	*(memory.p32++) = (long)0x4000000L + (long)((30 & 0x1f) << 27);
}
