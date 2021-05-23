/*****************************************************************************
  * sdt.h
  * Copyright (C) 2001-2011 VideoLAN
  * $Id$
  *
  * Authors: Johan Bilien <jobi@via.ecp.fr>
  *          Jean-Paul Saman <jpsaman@videolan.org>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
  *
  *****************************************************************************/
  
 #ifndef _DVBPSI_SDT_H_
 #define _DVBPSI_SDT_H_
  
 #ifdef __cplusplus
 extern "C" {
 #endif
  
 /*****************************************************************************
  * dvbpsi_sdt_service_t
  *****************************************************************************/
 typedef struct dvbpsi_sdt_service_s
 {
   uint16_t                  i_service_id;           
   bool                      b_eit_schedule;         
   bool                      b_eit_present;          
   uint8_t                   i_running_status;       
   bool                      b_free_ca;              
   uint16_t                  i_descriptors_length;   
   dvbpsi_descriptor_t *     p_first_descriptor;     
   struct dvbpsi_sdt_service_s * p_next;             
 } dvbpsi_sdt_service_t;
  
 /*****************************************************************************
  * dvbpsi_sdt_t
  *****************************************************************************/
 typedef struct dvbpsi_sdt_s
 {
     /* PSI table members */
     uint8_t                   i_table_id;         
     uint16_t                  i_extension;        
     /* Table specific */
     uint8_t                   i_version;          
     bool                      b_current_next;     
     uint16_t                  i_network_id;       
     dvbpsi_sdt_service_t *    p_first_service;    
 } dvbpsi_sdt_t;
  
 /*****************************************************************************
  * dvbpsi_sdt_callback
  *****************************************************************************/
 typedef void (* dvbpsi_sdt_callback)(void* p_priv, dvbpsi_sdt_t* p_new_sdt);
  
 /*****************************************************************************
  * dvbpsi_sdt_attach
  *****************************************************************************/
 bool dvbpsi_sdt_attach(dvbpsi_t *p_dvbpsi, uint8_t i_table_id, uint16_t i_extension,
                       dvbpsi_sdt_callback pf_callback, void* p_priv);
  
 /*****************************************************************************
  * dvbpsi_sdt_detach
  *****************************************************************************/
 void dvbpsi_sdt_detach(dvbpsi_t *p_dvbpsi, uint8_t i_table_id, uint16_t i_extension);
  
 /*****************************************************************************
  * dvbpsi_sdt_init/dvbpsi_NewSDT
  *****************************************************************************/
 void dvbpsi_sdt_init(dvbpsi_sdt_t *p_sdt, uint8_t i_table_id, uint16_t i_extension,
                      uint8_t i_version, bool b_current_next, uint16_t i_network_id);
  
 dvbpsi_sdt_t *dvbpsi_sdt_new(uint8_t i_table_id, uint16_t i_extension, uint8_t i_version,
                              bool b_current_next, uint16_t i_network_id);
  
 /*****************************************************************************
  * dvbpsi_sdt_empty/dvbpsi_sdt_delete
  *****************************************************************************/
 void dvbpsi_sdt_empty(dvbpsi_sdt_t *p_sdt);
  
 void dvbpsi_sdt_delete(dvbpsi_sdt_t *p_sdt);
  
 /*****************************************************************************
  * dvbpsi_sdt_service_add
  *****************************************************************************/
 dvbpsi_sdt_service_t *dvbpsi_sdt_service_add(dvbpsi_sdt_t* p_sdt,
     uint16_t i_service_id, bool b_eit_schedule, bool b_eit_present,
     uint8_t i_running_status, bool b_free_ca);
  
 /*****************************************************************************
  * dvbpsi_sdt_service_descriptor_add
  *****************************************************************************/
 dvbpsi_descriptor_t *dvbpsi_sdt_service_descriptor_add(
                                                dvbpsi_sdt_service_t *p_service,
                                                uint8_t i_tag, uint8_t i_length,
                                                uint8_t *p_data);
  
 /*****************************************************************************
  * dvbpsi_sdt_sections_generate
  *****************************************************************************
  * Generate SDT sections based on the dvbpsi_sdt_t structure.
  *****************************************************************************/
 dvbpsi_psi_section_t *dvbpsi_sdt_sections_generate(dvbpsi_t *p_dvbpsi, dvbpsi_sdt_t * p_sdt);
  
 #ifdef __cplusplus
 };
 #endif
  
 #else
 #error "Multiple inclusions of sdt.h"
 #endif
