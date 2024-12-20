#include "File.h"

namespace Axiom
{
	// holds the directory internally to File.cpp
	static char BaseDir[File::BASE_DIR_SIZE] = { 0 };

	File::Error File::ClearBaseDir() noexcept
	{
		memset(BaseDir, 0, sizeof(BaseDir));
		return Error::SUCCESS;
	}

	File::Error File::GetBaseDir(char *const pDirOut, size_t DirOutSize) noexcept
	{
		Error status = Error::SUCCESS;
		if (!pDirOut)
		{
			status = Error::BASE_DIR_NULLPTR_FAIL;
		}
		else if (DirOutSize < BASE_DIR_SIZE)
		{
			status = Error::BASE_DIR_INSUFFICIENT_SPACE_FAIL;
		}
		else
		{
			strcpy_s(pDirOut, DirOutSize, BaseDir);
		}

		return 	status;
	}

	File::Error File::SetBaseDir(const char *const pDir) noexcept
	{
		Error status = Error::SUCCESS;
		if (!pDir)
		{
			status = Error::BASE_DIR_NULLPTR_FAIL;
		}
		else if (strlen(pDir) > BASE_DIR_SIZE)
		{
			status = Error::BASE_DIR_INSUFFICIENT_SPACE_FAIL;
		}
		else
		{
			strcpy_s(BaseDir, BASE_DIR_SIZE, pDir);
		}

		return 	status;
	}

	bool File::IsHandleValid(Handle fh) noexcept
	{
		DWORD flags;
		if (!fh || !GetHandleInformation(fh, &flags))
		{
			return false;
		}

		return true;
	}

	File::Error File::Open(Handle &fh, const char *const fileName, Mode mode, bool UseBaseAddr) noexcept
	{
		Error status = Error::OPEN_FILENAME_FAIL;
		if (!fileName)
		{
			return status;
		}

		if (UseBaseAddr && !strlen(BaseDir))
		{
			return Error::OPEN_BASE_DIR_FAIL;
		}

		DWORD desiredAccess;
		switch (mode)
		{
		case Mode::READ:
			desiredAccess = GENERIC_READ;
			break;
		case Mode::WRITE:
			desiredAccess = GENERIC_WRITE;
			break;
		case Mode::READ_WRITE:
			desiredAccess = GENERIC_READ | GENERIC_WRITE;
			break;
		default:
			desiredAccess = GENERIC_READ;
			break;
		}

		char filepath[BASE_DIR_SIZE + 50];
		strcpy_s(filepath, sizeof(filepath), fileName);

		if (UseBaseAddr)
		{
			strcpy_s(filepath, sizeof(filepath), BaseDir);
			strcat_s(filepath, sizeof(filepath), fileName);
		}

		fh = CreateFile(filepath, desiredAccess, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (fh == INVALID_HANDLE_VALUE)
		{
			status = Error::OPEN_FAIL;
		}
		else
		{
			status = Error::SUCCESS;
		}

		return status;
	}

	File::Error File::Close(Handle &fh) noexcept
	{
		Error status = Error::CLOSE_FAIL;
		if (IsHandleValid(fh))
		{
			CloseHandle(fh);
			status = Error::SUCCESS;
		}

		return 	status;
	}

	File::Error File::Write(Handle fh, const void *const buffer, const DWORD inSize) noexcept
	{
		Error status = Error::WRITE_FAIL;
		if (!buffer || inSize == 0xFFFFFFFF)
		{
			return status;
		}

		DWORD numBytesWritten;
		if (WriteFile(fh, buffer, inSize, &numBytesWritten, nullptr))
		{
			status = Error::SUCCESS;
		}

		return status;
	}

	File::Error File::Read(Handle fh, void *const buffer, const DWORD inSize) noexcept
	{
		Error status = Error::READ_FAIL;
		if (!buffer || inSize == 0xFFFFFFFF)
		{
			return status;
		}

		DWORD numBytesRead = 0ul;
		if (ReadFile(fh, buffer, inSize, &numBytesRead, nullptr))
		{
			status = Error::SUCCESS;
		}

		return status;
	}

	File::Error File::Seek(Handle fh, Position location, int offset) noexcept
	{
		Error status = Error::SUCCESS;

		DWORD moveMethod;
		switch (location)
		{
		case Position::BEGIN:
			moveMethod = FILE_BEGIN;
			break;
		case Position::CURRENT:
			moveMethod = FILE_CURRENT;
			break;
		case Position::END:
			moveMethod = FILE_END;
			break;
		default:
			moveMethod = FILE_BEGIN;
			break;
		}

		DWORD currPos = SetFilePointer(fh, offset, nullptr, moveMethod);
		if (currPos == INVALID_SET_FILE_POINTER || currPos < 0)
		{
			status = Error::SEEK_FAIL;
		}

		return status;
	}

	File::Error File::Tell(Handle fh, DWORD &offset) noexcept
	{
		offset = SetFilePointer(fh, 0, nullptr, FILE_CURRENT);
		if (offset == INVALID_SET_FILE_POINTER || offset < 0)
		{
			return Error::TELL_FAIL;
		}

		return 	Error::SUCCESS;
	}

	File::Error File::Flush(Handle fh) noexcept
	{
		if (FlushFileBuffers(fh))
		{
			return Error::SUCCESS;
		}

		return Error::FLUSH_FAIL;
	}

}
