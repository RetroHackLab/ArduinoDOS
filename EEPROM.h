/*
  EEPROM.h - Per-EEPROM class library for Arduino & Teensy
  Copyright (c) 2006 David A. Mellis.  All right reserved.
  Modified by Ben Combee <bcombee@mac.com>
  Modified by Christopher Andrews <mclean.andrews@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
*/

#ifndef EEPROM_h
#define EEPROM_h

#include <stdint.h>
#include <avr/eeprom.h>

/***
    EERef class.
    
    This object is a proxy class that simulates a single byte reference 
    to an EEPROM address. It allows reading and writing via assignment.
***/
struct EERef {
    EERef( const int index ) : index( index ) {}
    
    // Access/Value assigns.
    uint8_t operator*() const            { return eeprom_read_byte( (uint8_t*) index ); }
    operator uint8_t() const             { return **this; }
    EERef &operator=( const EERef &ref ) { return *this = *ref; }
    
    EERef &operator=( uint8_t in ) {
        eeprom_write_byte( (uint8_t*) index, in );
        return *this;
    }
    
    // Prefix/Postfix increment/decrement
    EERef &operator++()    { *this = **this + 1; return *this; }
    EERef &operator--()    { *this = **this - 1; return *this; }
    uint8_t operator++(int){ uint8_t v = **this; *this = v + 1; return v; }
    uint8_t operator--(int){ uint8_t v = **this; *this = v - 1; return v; }

    int index; // Address of the byte
};

/***
    EEPtr class.
    
    This object is an EEPROM address pointer simulator.
    It acts like a normal pointer and can be incremented or decremented.
***/
struct EEPtr {
    EEPtr( const int index ) : index( index ) {}
    
    operator int() const          { return index; }
    EEPtr &operator=( int in )    { index = in; return *this; }
    
    // Prefix/Postfix increment/decrement
    EEPtr &operator++()           { index++; return *this; }
    EEPtr &operator--()           { index--; return *this; }
    EEPtr operator++(int)         { EEPtr p = *this; index++; return p; }
    EEPtr operator--(int)         { EEPtr p = *this; index--; return p; }
    
    EERef operator*() const       { return index; }
    
    int index;
};

/***
    EEPROMClass class.
    
    This object presents the user interface for interacting with the EEPROM.
***/
class EEPROMClass {
public:
    // Basic functions
    EERef operator[]( const int idx ) { return idx; }
    uint8_t read( int idx )           { return eeprom_read_byte( (uint8_t*) idx ); }
    void write( int idx, uint8_t val ) { eeprom_write_byte( (uint8_t*) idx, val ); }
    void update( int idx, uint8_t val ){ eeprom_update_byte( (uint8_t*) idx, val ); }
    
    // Advanced templated functions for structures/objects (32-bit types, etc.)
    template< typename T > T &get( int idx, T &t ) {
        uint8_t *ptr = (uint8_t*) &t;
        for ( int count = sizeof(T) ; count ; --count, ++idx ) {
            *ptr++ = read( idx );
        }
        return t;
    }
    
    template< typename T > const T &put( int idx, const T &t ) {
        const uint8_t *ptr = (const uint8_t*) &t;
        for ( int count = sizeof(T) ; count ; --count, ++idx ) {
            update( idx, *ptr++ );
        }
        return t;
    }
    
    // Get total number of bytes available in the hardware EEPROM
    uint16_t length() { return E2END + 1; }
    
    // STL style iterators
    EEPtr begin()     { return 0; }
    EEPtr end()       { return length(); }
};

// Global object created for the user to call directly: EEPROM.read(), etc.
extern EEPROMClass EEPROM;

#endif
