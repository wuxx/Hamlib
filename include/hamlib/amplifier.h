/*
 *  Hamlib Interface - Amplifier API header
 *  Copyright (c) 2000-2005 by Stephane Fillod
 *
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef _AMPLIFIER_H
#define _AMPLIFIER_H 1

#include <hamlib/rig.h>
#include <hamlib/amplist.h>

/**
 * \addtogroup amp
 * @{
 */

/**
 *  \file amp.h
 *  \brief Hamlib amplifier data structures.
 *
 *  This file contains the data structures and declarations for the Hamlib
 *  amplifier API.  see the amplifier.c file for more details on the amplifier API.
 */



__BEGIN_DECLS

/* Forward struct references */

struct amp;
struct amp_state;


/**
 *  \typedef typedef struct amp AMP
 *  \brief Amplifier structure definition (see amp for details).
 */
typedef struct amp AMP;


/**
 *  \typedef typedef float swr_t
 *  \brief Type definition for SWR.
 *
 *  The swr_t type is used as a parameter for the amp_get_swr() function.
 *
 *  Unless specified otherwise, the unit of swr_t is 1.0 to max reported by tuner
 */
typedef float swr_t;


/**
 *  \typedef typedef float tune_value_t
 *  \brief Type definition for tuning values capacitance and resistance.
 *
 *  The tune_value_t type is used as a parameter for the amp_get_level()
 *
 *  Unless specified otherwise, the units of tune_value_t is pF and nH
 */
typedef int tune_value_t;


/**
 * \brief Token in the netampctl protocol for returning error code
 */
#define NETAMPCTL_RET "RPRT "


typedef enum
{
  AMP_RESET_MEM, // erase tuner memory
  AMP_RESET_FAULT, // reset any fault
  AMP_RESET_AMP  // for kpa1500
} amp_reset_t;

/**
 * \brief Amplifier type flags
 */
typedef enum
{
  AMP_FLAG_1 = (1 << 1),      /*!< TBD */
  AMP_FLAG_2 = (1 << 2)       /*!< TBD */
} amp_type_t;

// TBD AMP_TYPE
#define AMP_TYPE_MASK (AMP_FLAG_1|AMP_FLAG_2)

#define AMP_TYPE_OTHER 0
#define AMP_TYPE_1     AMP_FLAG_1
#define AMP_TYPE_2     AMP_FLAG_2
#define AMP_TYPE_ALL       (AMP_FLAG_1|AMP_FLAG_2)


enum amp_level_e
{
  AMP_LEVEL_NONE          = 0,        /*!< '' -- No Level */
  AMP_LEVEL_SWR           = (1 << 0), /*!< \c SWR 1.0 or greater */
  AMP_LEVEL_NH            = (1 << 1), /*!< \c Tune setting nanohenries */
  AMP_LEVEL_PF            = (1 << 2), /*!< \c Tune setting picofarads */
  AMP_LEVEL_PWR_INPUT     = (1 << 3), /*!< \c Power reading from amp */
  AMP_LEVEL_PWR_FWD       = (1 << 4), /*!< \c Power reading forward */
  AMP_LEVEL_PWR_REFLECTED = (1 << 5), /*!< \c Power reading reverse */
  AMP_LEVEL_PWR_PEAK      = (1 << 6), /*!< \c Power reading peak */
  AMP_LEVEL_FAULT         = (1 << 7)  /*!< \c Fault code */
};

#define AMP_LEVEL_FLOAT_LIST  (AMP_LEVEL_SWR)
#define AMP_LEVEL_STRING_LIST  (AMP_LEVEL_FAULT)
#define AMP_LEVEL_IS_FLOAT(l) ((l)&AMP_LEVEL_FLOAT_LIST)
#define AMP_LEVEL_IS_STRING(l) ((l)&AMP_LEVEL_STRING_LIST)

/**
 *  \def AMP_MOVE_UP
 *  \brief A macro that returns the flag for the \b UP direction.
 *
 *  This macro defines the value of the \b UP direction which can be
 *  used with the amp_move() function.
 *
 *  \sa amp_move(), AMP_MOVE_DOWN, AMP_MOVE_LEFT, AMP_MOVE_CCW,
 *      AMP_MOVE_RIGHT, AMP_MOVE_CW
 */
#define AMP_MOVE_UP         (1<<1)

/**
 *  \def AMP_MOVE_DOWN
 *  \brief A macro that returns the flag for the \b DOWN direction.
 *
 *  This macro defines the value of the \b DOWN direction which can be
 *  used with the amp_move() function.
 *
 *  \sa amp_move(), AMP_MOVE_UP, AMP_MOVE_LEFT, AMP_MOVE_CCW, AMP_MOVE_RIGHT,
 *      AMP_MOVE_CW
*/
#define AMP_MOVE_DOWN       (1<<2)

/**
 *  \def AMP_MOVE_LEFT
 *  \brief A macro that returns the flag for the \b LEFT direction.
 *
 *  This macro defines the value of the \b LEFT direction which can be
 *  used with the amp_move function.
 *
 *  \sa amp_move(), AMP_MOVE_UP, AMP_MOVE_DOWN, AMP_MOVE_CCW, AMP_MOVE_RIGHT,
 *      AMP_MOVE_CW
 */
#define AMP_MOVE_LEFT       (1<<3)

/**
 *  \def AMP_MOVE_CCW
 *  \brief A macro that returns the flag for the \b counterclockwise direction.
 *
 *  This macro defines the value of the \b counterclockwise direction which
 *  can be used with the amp_move() function. This value is equivalent to
 *  AMP_MOVE_LEFT .
 *
 *  \sa amp_move(), AMP_MOVE_UP, AMP_MOVE_DOWN, AMP_MOVE_LEFT, AMP_MOVE_RIGHT,
 *      AMP_MOVE_CW
 */
#define AMP_MOVE_CCW        AMP_MOVE_LEFT

/**
 *  \def AMP_MOVE_RIGHT
 *  \brief A macro that returns the flag for the \b RIGHT direction.
 *
 *  This macro defines the value of the \b RIGHT direction which can be used
 *  with the amp_move() function.
 *
 *  \sa amp_move(), AMP_MOVE_UP, AMP_MOVE_DOWN, AMP_MOVE_LEFT, AMP_MOVE_CCW,
 *      AMP_MOVE_CW
 */
#define AMP_MOVE_RIGHT      (1<<4)

/**
 *  \def AMP_MOVE_CW
 *  \brief A macro that returns the flag for the \b clockwise direction.
 *
 *  This macro defines the value of the \b clockwise direction wich can be
 *  used with the amp_move() function. This value is equivalent to
 *  AMP_MOVE_RIGHT .
 *
 *  \sa amp_move(), AMP_MOVE_UP, AMP_MOVE_DOWN, AMP_MOVE_LEFT, AMP_MOVE_CCW,
 *      AMP_MOVE_RIGHT
 */
#define AMP_MOVE_CW         AMP_MOVE_RIGHT


/* Basic amp type, can store some useful info about different amplifiers. Each
 * lib must be able to populate this structure, so we can make useful
 * enquiries about capablilities.
 */

/**
 * Amplifier Caps
 * \struct amp_caps
 * \brief Amplifier data structure.
 *
 * The main idea of this struct is that it will be defined by the backend
 * amplifier driver, and will remain readonly for the application.  Fields that
 * need to be modifiable by the application are copied into the struct
 * amp_state, which is a kind of private of the AMP instance.
 *
 * This way, you can have several rigs running within the same application,
 * sharing the struct amp_caps of the backend, while keeping their own
 * customized data.
 *
 * n.b.: Don't move fields around, as the backends depend on it when
 *       initializing their caps.
 */
struct amp_caps
{
  amp_model_t amp_model;                      /*!< Amplifier model. */
  const char *model_name;                     /*!< Model name. */
  const char *mfg_name;                       /*!< Manufacturer. */
  const char *version;                        /*!< Driver version. */
  const char *copyright;                      /*!< Copyright info. */
  enum rig_status_e status;                   /*!< Driver status. */

  int amp_type;                               /*!< Amplifier type. */
  enum rig_port_e port_type;                  /*!< Type of communication port. */

  int serial_rate_min;                        /*!< Minimal serial speed. */
  int serial_rate_max;                        /*!< Maximal serial speed. */
  int serial_data_bits;                       /*!< Number of data bits. */
  int serial_stop_bits;                       /*!< Number of stop bits. */
  enum serial_parity_e serial_parity;         /*!< Parity. */
  enum serial_handshake_e serial_handshake;   /*!< Handshake. */

  int write_delay;                            /*!< Write delay. */
  int post_write_delay;                       /*!< Post-write delay. */
  int timeout;                                /*!< Timeout. */
  int retry;                                  /*!< Number of retry if command fails. */

  const struct confparams *cfgparams;         /*!< Configuration parametres. */
  const rig_ptr_t priv;                       /*!< Private data. */

  setting_t has_get_level;
  setting_t has_set_level;

  gran_t level_gran[RIG_SETTING_MAX]; /*!< level granularity */
  gran_t parm_gran[RIG_SETTING_MAX]; /*!< level granularity */

  /*
   * Amp Admin API
   *
   */

  int (*amp_init)(AMP *amp);
  int (*amp_cleanup)(AMP *amp);
  int (*amp_open)(AMP *amp);
  int (*amp_close)(AMP *amp);

  int (*set_freq)(AMP *amp, freq_t val);
  int (*get_freq)(AMP *amp, freq_t *val);

  int (*set_conf)(AMP *amp, token_t token, const char *val);
  int (*get_conf)(AMP *amp, token_t token, char *val);

  /*
   *  General API commands, from most primitive to least.. :()
   *  List Set/Get functions pairs
   */

  int (*reset)(AMP *amp, amp_reset_t reset);
  int (*get_level)(AMP *amp, setting_t level, value_t *val);
  int (*get_ext_level)(AMP *amp, token_t level, value_t *val);
  int (*set_powerstat)(AMP *amp, powerstat_t status);
  int (*get_powerstat)(AMP *amp, powerstat_t *status);


  /* get firmware info, etc. */
  const char *(*get_info)(AMP *amp);

  setting_t levels;
  unsigned ext_levels;
  const struct confparams *extlevels;
  const struct confparams *extparms;
};


/**
 * Amplifier state
 * \struct amp_state
 * \brief Live data and customized fields.
 *
 * This struct contains live data, as well as a copy of capability fields
 * that may be updated (ie. customized)
 *
 * It is fine to move fields around, as this kind of struct should
 * not be initialized like caps are.
 */
struct amp_state
{
  /*
   * overridable fields
   */

  /*
   * non overridable fields, internal use
   */
  hamlib_port_t ampport;  /*!< Amplifier port (internal use). */

  int comm_state;         /*!< Comm port state, opened/closed. */
  rig_ptr_t priv;         /*!< Pointer to private amplifier state data. */
  rig_ptr_t obj;          /*!< Internal use by hamlib++ for event handling. */

  setting_t has_get_level;

  gran_t level_gran[RIG_SETTING_MAX]; /*!< level granularity */
  gran_t parm_gran[RIG_SETTING_MAX]; /*!< level granularity */
};


/**
 * Amplifier structure
 * \struct amp
 * \brief This is the master data structure,
 * acting as a handle for the controlled amplifier.
 *
 * This is the master data structure, acting as a handle for the controlled
 * amplifier. A pointer to this structure is returned by the amp_init() API
 * function and is passed as a parameter to every amplifier specific API call.
 *
 * \sa amp_init(), amp_caps(), amp_state()
 */
struct amp
{
  struct amp_caps *caps;      /*!< Amplifier caps. */
  struct amp_state state;     /*!< Amplifier state. */
};


/* --------------- API function prototypes -----------------*/

extern HAMLIB_EXPORT(AMP *)
amp_init HAMLIB_PARAMS((amp_model_t amp_model));

extern HAMLIB_EXPORT(int)
amp_open HAMLIB_PARAMS((AMP *amp));

extern HAMLIB_EXPORT(int)
amp_close HAMLIB_PARAMS((AMP *amp));

extern HAMLIB_EXPORT(int)
amp_cleanup HAMLIB_PARAMS((AMP *amp));

extern HAMLIB_EXPORT(int)
amp_set_conf HAMLIB_PARAMS((AMP *amp,
                            token_t token,
                            const char *val));
extern HAMLIB_EXPORT(int)
amp_get_conf HAMLIB_PARAMS((AMP *amp,
                            token_t token,
                            char *val));
extern HAMLIB_EXPORT(int)
amp_set_powerstat HAMLIB_PARAMS((AMP *amp,
                                 powerstat_t status));
extern HAMLIB_EXPORT(int)
amp_get_powerstat HAMLIB_PARAMS((AMP *amp,
                                 powerstat_t *status));


/*
 *  General API commands, from most primitive to least.. )
 *  List Set/Get functions pairs
 */
extern HAMLIB_EXPORT(int)
amp_get_freq HAMLIB_PARAMS((AMP *amp,
                            freq_t *freq));
extern HAMLIB_EXPORT(int)
amp_set_freq HAMLIB_PARAMS((AMP *amp,
                            freq_t freq));

extern HAMLIB_EXPORT(int)
amp_reset HAMLIB_PARAMS((AMP *amp,
                         amp_reset_t reset));

extern HAMLIB_EXPORT(const char *)
amp_get_info HAMLIB_PARAMS((AMP *amp));

extern HAMLIB_EXPORT(int)
amp_get_level HAMLIB_PARAMS((AMP *amp, setting_t level, value_t *val));

extern HAMLIB_EXPORT(int)
amp_register HAMLIB_PARAMS((const struct amp_caps *caps));

extern HAMLIB_EXPORT(int)
amp_unregister HAMLIB_PARAMS((amp_model_t amp_model));

extern HAMLIB_EXPORT(int)
amp_list_foreach HAMLIB_PARAMS((int (*cfunc)(const struct amp_caps *,
                                rig_ptr_t),
                                rig_ptr_t data));

extern HAMLIB_EXPORT(int)
amp_load_backend HAMLIB_PARAMS((const char *be_name));

extern HAMLIB_EXPORT(int)
amp_check_backend HAMLIB_PARAMS((amp_model_t amp_model));

extern HAMLIB_EXPORT(int)
amp_load_all_backends HAMLIB_PARAMS((void));

extern HAMLIB_EXPORT(amp_model_t)
amp_probe_all HAMLIB_PARAMS((hamlib_port_t *p));

extern HAMLIB_EXPORT(int)
amp_token_foreach HAMLIB_PARAMS((AMP *amp,
                                 int (*cfunc)(const struct confparams *,
                                     rig_ptr_t),
                                 rig_ptr_t data));

extern HAMLIB_EXPORT(const struct confparams *)
amp_confparam_lookup HAMLIB_PARAMS((AMP *amp,
                                    const char *name));

extern HAMLIB_EXPORT(token_t)
amp_token_lookup HAMLIB_PARAMS((AMP *amp,
                                const char *name));

extern HAMLIB_EXPORT(const struct amp_caps *)
amp_get_caps HAMLIB_PARAMS((amp_model_t amp_model));

extern HAMLIB_EXPORT(setting_t)
amp_has_get_level HAMLIB_PARAMS((AMP *amp,
                                 setting_t level));

extern HAMLIB_EXPORT(const struct confparams *)
amp_ext_lookup HAMLIB_PARAMS((AMP *amp,
                              const char *name));

extern HAMLIB_EXPORT(int)
amp_get_ext_level HAMLIB_PARAMS((AMP *amp,
                                 token_t token,
                                 value_t *val));

extern HAMLIB_EXPORT(const char *) amp_strlevel(setting_t);

extern HAMLIB_EXPORT(const struct confparams *)
rig_ext_lookup HAMLIB_PARAMS((RIG *rig,
                              const char *name));


/**
 *  \def amp_debug
 *  \brief Convenience definition for debug level.
 *
 *  This is just as convenience definition of the amplifier debug level,
 *  and is the same as for the rig debug level.
 *
 *  \sa rig_debug()
 */
#define amp_debug rig_debug

__END_DECLS

#endif /* _AMPLIFIER_H */

/** @} */
