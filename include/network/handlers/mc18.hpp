/*
 * hCraft 2 - A revised custom Minecraft server.
 * Copyright (C) 2015 Jacob Zhitomirsky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _hCraft2__NETWORK__HANDLERS__MC18__H_
#define _hCraft2__NETWORK__HANDLERS__MC18__H_

#include "network/packet_handler.hpp"


namespace hc {
  
  // forward decs:
  class mc18_packet_builder;
  class player;
  
  /* 
   * The packet handler for the 1.8 (bountiful update) client version.
   */
  class mc18_packet_handler: public packet_handler
  {
  private:
    enum protocol_state
    {
      PS_HANDSHAKE = 0,
      PS_STATUS    = 1,
      PS_LOGIN     = 2,
      PS_PLAY      = 3,
    };
    
  private:
    protocol_state state;
    mc18_packet_builder *builder;
    player *pl;
    
    // encryption stuff:
    unsigned char vtoken[4]; // verification token
  
  public:
    mc18_packet_handler ();
    ~mc18_packet_handler ();
    
  private:
    void login ();
    
  private:
    void handle_xx (packet_reader& reader); // dummy handler
    
    // handshaking:
    
    virtual void handle_h00 (packet_reader& reader); // handshake
    
    // status:
    
    virtual void handle_s00 (packet_reader& reader); // status request
    virtual void handle_s01 (packet_reader& reader); // status ping
    
    // login:
    
    virtual void handle_l00 (packet_reader& reader); // login start
    virtual void handle_l01 (packet_reader& reader); // encryption response
    
    // play:
    
    virtual void handle_p00 (packet_reader& reader);
    virtual void handle_p01 (packet_reader& reader);
    virtual void handle_p03 (packet_reader& reader);
    virtual void handle_p04 (packet_reader& reader);
    virtual void handle_p05 (packet_reader& reader);
    virtual void handle_p06 (packet_reader& reader);
    
  public:
    /* 
     * Handles the specified packet, by dispatching it to the appropriate
     * handler function.
     */
    virtual void handle (packet_reader& reader) override;
    
    virtual void set_connection (connection *conn) override;
    
    virtual void disconnect () override;
    
    virtual void tick () override;
  };
}

#endif

