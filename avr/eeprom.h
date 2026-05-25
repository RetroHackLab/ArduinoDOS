#ifndef _AVR_EEPROM_H_
#define _AVR_EEPROM_H_ 1

#define __need_size_t
#include <avr/stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Macros de lecture (Byte, Word, Double-Word/32-bit)
#define eeprom_read_byte(addr) \
    __builtin_avr_eeprom_read_byte((const uint8_t *)(addr))

#define eeprom_read_word(addr) \
    __builtin_avr_eeprom_read_word((const uint16_t *)(addr))

#define eeprom_read_dword(addr) \
    __builtin_avr_eeprom_read_dword((const uint32_t *)(addr))

#define eeprom_read_block(pointer_ram, pointer_eeprom, n) \
    __builtin_avr_eeprom_read_block((void *)(pointer_ram), (const void *)(pointer_eeprom), (size_t)(n))

// Macros d'écriture brute
#define eeprom_write_byte(addr, value) \
    __builtin_avr_eeprom_write_byte((uint8_t *)(addr), (uint8_t)(value))

#define eeprom_write_word(addr, value) \
    __builtin_avr_eeprom_write_word((uint16_t *)(addr), (uint16_t)(value))

#define eeprom_write_dword(addr, value) \
    __builtin_avr_eeprom_write_dword((uint32_t *)(addr), (uint32_t)(value))

#define eeprom_write_block(pointer_ram, pointer_eeprom, n) \
    __builtin_avr_eeprom_write_block((const void *)(pointer_ram), (void *)(pointer_eeprom), (size_t)(n))

// Macros d'optimisation d'écriture (mise à jour uniquement si la valeur change)
#define eeprom_update_byte(addr, value) \
    __builtin_avr_eeprom_update_byte((uint8_t *)(addr), (uint8_t)(value))

#define eeprom_update_word(addr, value) \
    __builtin_avr_eeprom_update_word((uint16_t *)(addr), (uint16_t)(value))

#define eeprom_update_dword(addr, value) \
    __builtin_avr_eeprom_update_dword((uint32_t *)(addr), (uint32_t)(value))

// Vérification de l'état de la mémoire
#define eeprom_is_ready() \
    __builtin_avr_eeprom_is_ready()

#define eeprom_busy_wait() \
    do {} while (!eeprom_is_ready())

#ifdef __cplusplus
}
#endif

#endif /* _AVR_EEPROM_H_ */
