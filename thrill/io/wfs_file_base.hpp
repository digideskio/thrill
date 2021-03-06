/*******************************************************************************
 * thrill/io/wfs_file_base.hpp
 *
 * Windows file system file base
 *
 * Copied and modified from STXXL https://github.com/stxxl/stxxl, which is
 * distributed under the Boost Software License, Version 1.0.
 *
 * Part of Project Thrill - http://project-thrill.org
 *
 * Copyright (C) 2005 Roman Dementiev <dementiev@ira.uka.de>
 * Copyright (C) 2008, 2010 Andreas Beckmann <beckmann@cs.uni-frankfurt.de>
 * Copyright (C) 2009, 2010 Johannes Singler <singler@kit.edu>
 *
 * All rights reserved. Published under the BSD-2 license in the LICENSE file.
 ******************************************************************************/

#pragma once
#ifndef THRILL_IO_WFS_FILE_BASE_HEADER
#define THRILL_IO_WFS_FILE_BASE_HEADER

#include <thrill/common/config.hpp>

#if THRILL_WINDOWS

#include <thrill/io/file_base.hpp>
#include <thrill/io/request.hpp>

#include <mutex>
#include <string>

namespace thrill {
namespace io {

//! \addtogroup io_layer_fileimpl
//! \{

//! Base for Windows file system implementations.
class WfsFileBase : public virtual FileBase
{
protected:
    using HANDLE = void*;

    std::mutex fd_mutex_;  // sequentialize function calls involving file_des_
    HANDLE file_des_;      // file descriptor
    int mode_;             // open mode
    const std::string filename;
    offset_type bytes_per_sector;
    bool locked;
    WfsFileBase(const std::string& filename, int mode);
    offset_type _size();
    void close();

public:
    ~WfsFileBase();
    offset_type size() final;
    void set_size(offset_type newsize) final;
    void lock() final;
    const char * io_type() const override;
    void close_remove() final;
};

//! \}

} // namespace io
} // namespace thrill

#endif // THRILL_WINDOWS

#endif // !THRILL_IO_WFS_FILE_BASE_HEADER

/******************************************************************************/
