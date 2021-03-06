// Copyright (c) 2014-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_JSON_PEGTL_INTERNAL_FILE_MAPPER_POSIX_HPP
#define TAO_JSON_PEGTL_INTERNAL_FILE_MAPPER_POSIX_HPP

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <filesystem>
#include <utility>

#include "../config.hpp"

namespace TAO_JSON_PEGTL_NAMESPACE::internal
{
   struct file_opener
   {
      explicit file_opener( const std::filesystem::path& path )  // NOLINT(modernize-pass-by-value)
         : m_path( path ),
           m_fd( open() )
      {}

      file_opener( const file_opener& ) = delete;
      file_opener( file_opener&& ) = delete;

      ~file_opener()
      {
         ::close( m_fd );
      }

      void operator=( const file_opener& ) = delete;
      void operator=( file_opener&& ) = delete;

      [[nodiscard]] std::size_t size() const
      {
         struct stat st;
         errno = 0;
         if( ::fstat( m_fd, &st ) < 0 ) {
            const std::error_code ec( errno, std::system_category() );
            throw std::filesystem::filesystem_error( "fstat() failed", m_path, ec );
         }
         return std::size_t( st.st_size );
      }

      const std::filesystem::path m_path;
      const int m_fd;

   private:
      [[nodiscard]] int open() const
      {
         errno = 0;
         const int fd = ::open( m_path.c_str(),
                                O_RDONLY
#if defined( O_CLOEXEC )
                                   | O_CLOEXEC
#endif
         );
         if( fd >= 0 ) {
            return fd;
         }
         const std::error_code ec( errno, std::system_category() );
         throw std::filesystem::filesystem_error( "open() failed", m_path, ec );
      }
   };

   class file_mapper
   {
   public:
      explicit file_mapper( const std::filesystem::path& path )
         : file_mapper( file_opener( path ) )
      {}

      explicit file_mapper( const file_opener& reader )
         : m_size( reader.size() ),
           m_data( static_cast< const char* >( ::mmap( nullptr, m_size, PROT_READ, MAP_PRIVATE, reader.m_fd, 0 ) ) )
      {
         if( ( m_size != 0 ) && ( intptr_t( m_data ) == -1 ) ) {
            const std::error_code ec( errno, std::system_category() );
            throw std::filesystem::filesystem_error( "mmap() failed", reader.m_path, ec );
         }
      }

      file_mapper( const file_mapper& ) = delete;
      file_mapper( file_mapper&& ) = delete;

      ~file_mapper()
      {
         // Legacy C interface requires pointer-to-mutable but does not write through the pointer.
         ::munmap( const_cast< char* >( m_data ), m_size );
      }

      void operator=( const file_mapper& ) = delete;
      void operator=( file_mapper&& ) = delete;

      [[nodiscard]] bool empty() const noexcept
      {
         return m_size == 0;
      }

      [[nodiscard]] std::size_t size() const noexcept
      {
         return m_size;
      }

      using iterator = const char*;
      using const_iterator = const char*;

      [[nodiscard]] iterator data() const noexcept
      {
         return m_data;
      }

      [[nodiscard]] iterator begin() const noexcept
      {
         return m_data;
      }

      [[nodiscard]] iterator end() const noexcept
      {
         return m_data + m_size;
      }

   private:
      const std::size_t m_size;
      const char* const m_data;
   };

}  // namespace TAO_JSON_PEGTL_NAMESPACE::internal

#endif
