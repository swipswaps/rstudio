 * Copyright (C) 2009-19 by RStudio, PBC
namespace rstudio {
namespace core {
namespace system {

class User;

}
}
}
#ifndef _WIN32

/**
 * @enum FileMode
 * Represents all possible posix file modes.
 */
enum class FileMode
{
   USER_READ_WRITE,
   USER_READ_WRITE_EXECUTE,
   USER_READ_WRITE_GROUP_READ,
   USER_READ_WRITE_ALL_READ,
   USER_READ_WRITE_EXECUTE_ALL_READ_EXECUTE,
   ALL_READ,
   ALL_READ_WRITE,
   ALL_READ_WRITE_EXECUTE
};

#endif

#ifdef _WIN32
#ifndef _WIN32
   /**
    * @brief Changes the file mode to the specified file mode.
    *
    * @param in_fileModeStr     The posix file mode string. e.g. rwxr-xr-x.
    *
    * @return Success if the file mode could be changed; Error otherwise.
    */
   Error changeFileMode(const std::string& in_fileModeStr) const;

   /**
    * @brief Changes the file mode to the specified file mode.
    *
    * @param in_fileMode        The new file mode.
    * @param in_setStickyBit    Whether to set the sticky bit on this file.
    *
    * @return Success if the file mode could be changed; Error otherwise.
    */
   Error changeFileMode(FileMode in_fileMode, bool in_setStickyBit = false) const;

   /**
    * @brief Changes the ownership of the file or directory to the specified user.
    *
    * @param in_newUser         The user who should own the file.
    * @param in_recursive       If this FilePath is a directory, whether to recursively change ownership on all files
    *                           and directories within this directory.
    * @param in_shouldChown     A recursive iteration function which allows the caller to filter files and directories.
    *                           If a file or directory should have its ownership changed, this function should return
    *                           true.
    *
    * @return Success if the file, and optionally all nested files and directories, had their ownership changed; Error
    *         otherwise.
    */
   Error changeOwnership(
      const system::User& in_newUser,
      bool in_recursive = false,
      const RecursiveIterationFunction& in_shouldChown = RecursiveIterationFunction()) const;
#endif

#ifndef _WIN32
   /**
    * @brief Gets the posix file mode of this file or directory.
    *
    * @param out_fileMode   The file mode of this file or directory. Invalid if an error is returned.
    *
    * @return Success if the file mode could be retrieved; Error otherwise.
    */
   Error getFileMode(FileMode& out_fileMode) const;
#endif

   /**
    * @brief Checks if a file can be written to by opening the file.
    *
    * To be successful, the file must already exist on the system.
    * If write access is not absolutely necessary, use isFileWriteable from FileMode.hpp.
    *
    * @return Success if file can be written to; system error otherwise (e.g. EPERM, ENOENT, etc.)
    */
   Error testWritePermissions() const;
