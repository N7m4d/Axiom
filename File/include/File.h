#ifndef FILE_H
#define FILE_H

namespace Axiom
{
	class File
	{
	public:

		// Constants for the library
		static const uint32_t MAJOR_VERSION = 3;
		static const uint32_t MINOR_VERSION = 0;
		// hide the base directory.. in File.cpp
		static const uint32_t BASE_DIR_SIZE = 128;

		typedef void* Handle;

		enum class Mode : uint32_t
		{
			READ,
			WRITE,
			READ_WRITE
		};

		enum class Position : uint32_t
		{
			BEGIN,
			CURRENT,
			END
		};

		enum class Error : uint32_t
		{
			SUCCESS,
			BASE_DIR_FAIL,
			BASE_DIR_NULLPTR_FAIL,
			BASE_DIR_INSUFFICIENT_SPACE_FAIL,
			OPEN_FAIL,
			OPEN_FILENAME_FAIL,
			OPEN_BASE_DIR_FAIL,
			CLOSE_FAIL,
			WRITE_FAIL,
			READ_FAIL,
			SEEK_FAIL,
			TELL_FAIL,
			FLUSH_FAIL,
			UNDEFINED
		};

		static Error GetBaseDir(char * const pDirOut, size_t DirOutSize) noexcept;
		static Error SetBaseDir(const char *const pDir) noexcept;
		static Error ClearBaseDir() noexcept;

		static Error Open(Handle &fh, const char* const fileName, Mode mode, bool UseBaseAddr = false) noexcept;
		static Error Close(Handle &fh) noexcept;
		static Error Write(Handle fh, const void* const buffer, const DWORD inSize) noexcept;
		static Error Read(Handle fh, void* const _buffer, const DWORD _size) noexcept;
		static Error Seek(Handle fh, Position location, int offset) noexcept;
		static Error Tell(Handle fh, DWORD& offset) noexcept;
		static Error Flush(Handle fh) noexcept;
		static bool IsHandleValid(Handle fh) noexcept;
	};

}

#endif
