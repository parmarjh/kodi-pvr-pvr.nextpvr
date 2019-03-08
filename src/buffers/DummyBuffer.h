#pragma once
/*
*      Copyright (C) 2015 Sam Stenvall
*
*  This Program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*
*  This Program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with XBMC; see the file COPYING.  If not, write to
*  the Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
*  MA 02110-1301  USA
*  http://www.gnu.org/copyleft/gpl.html
*
*/

#include "Buffer.h"

using namespace ADDON;
namespace timeshift {

  /**
   * Dummy buffer that just passes all calls through to the input file
   * handle without actually buffering anything
   */
  class DummyBuffer : public Buffer
  {
  public:
    DummyBuffer() : Buffer() { XBMC->Log(LOG_NOTICE, "DummyBuffer created!"); }
    virtual ~DummyBuffer() {}
    
    virtual int Read(byte *buffer, size_t length) override
    {
      return XBMC->ReadFile(m_inputHandle, buffer, length);
    }

    virtual int64_t Seek(int64_t position, int whence) override
    {
      return -1; // we can't seek without a real buffer
    }

    virtual int64_t Position() const override
    {
      return XBMC->GetFilePosition(m_inputHandle);
    }

    virtual int64_t Length() const override
    {
      return XBMC->GetFileLength(m_inputHandle);
    }

    PVR_ERROR GetStreamTimes(PVR_STREAM_TIMES *) override;
  };
}
