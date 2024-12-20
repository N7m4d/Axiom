#ifdef MATH_USE_HINTS

		enum class Hint : uint32_t
		{
			Generalize = 0x0,        // generalize 4x4 inverse  (no flags)
			Rot = 0x1,               // matrix inverse is M.T()
			Trans = 0x2,             // matrix inverse is M(-trans)
			RotTrans = 0x3,          // rot and trans  A_inv is A.T() 
			Scale = 0x4,             // matrix invers is M(1/scale)
			RotScale = 0x5,          // Rot and Scale no translate
			TransScale = 0x6,        // Trans and Scale no Translate
			Affine = 0x7             // generalize Affine

		};

		inline void privClearHint()
		{
			this->_u_m15 &= (unsigned int)(0xFFFFFFF8);
		}

		inline void privSetGeneralHint()
		{
			this->_u_m15 &= (unsigned int)(0xFFFFFFF8);
		}

		inline void privSetScaleHint()
		{
			this->_u_m15 |= (unsigned int)(Mat4::Hint::Scale);
		}

		inline void privSetRotHint()
		{
			this->_u_m15 |= (unsigned int)(Mat4::Hint::Rot);
		}

		inline void privSetTransHint()
		{
			this->_u_m15 |= (unsigned int)(Mat4::Hint::Trans);
		}

		inline void privSetCopyHint() const
		{
			// do nothing
		}

		inline Hint privGetHint() const
		{
			Hint h;

			// test if m15 ~= 1.0f (ignore last 3 bits flags, actually 8 bits to account for noise)

			if((this->_u_m15 & 0xFFFFFF00) == 0x3f800000 || (this->_u_m15 & 0xFFFFFF00) == 0x3f7fff00)
			{
				h = (Hint)(this->_u_m15 & 0x7);
			}
			else
			{
				h = Hint::Generalize;
			}

			return h;
		}

		inline void privSetNewHint(Hint A, Hint B)
		{
			Hint h;

			if(A == Hint::Generalize || B == Hint::Generalize)
			{
				h = Hint::Generalize;
			}
			else // hint isn't a generalized matrix
			{
				h = (Hint)((unsigned int)A | (unsigned int)B);
			}

			// Set it.
			this->_u_m15 &= (unsigned int)0xFFFFFFF8;
			this->_u_m15 |= (unsigned int)h;
		}

#else

		enum class Hint : uint32_t
		{
			Generalize = 0x0,        // generalize 4x4 inverse  (no flags)
			Rot = 0x0,               // matrix inverse is M.T()
			Trans = 0x0,             // matrix inverse is M(-trans)
			RotTrans = 0x0,          // rot and trans  A_inv is A.T() 
			Scale = 0x0,             // matrix invers is M(1/scale)
			RotScale = 0x0,          // Rot and Scale no translate
			TransScale = 0x0,        // Trans and Scale no Translate
			Affine = 0x0             // generalize Affine
		};


		inline void privClearHint()
		{
		}

		inline void privSetGeneralHint()
		{	
		}

		inline void privSetScaleHint()
		{
		}

		inline void privSetRotHint()
		{
		}

		inline void privSetTransHint()
		{
		}

		inline void privSetCopyHint() const
		{
		}

		inline Hint privGetHint() const
		{

			return Hint::Generalize;
		}

		inline void privSetNewHint(Hint A, Hint B)
		{
			AZUL_UNUSED_VAR(A);
			AZUL_UNUSED_VAR(B);
		}


#endif
