#include <geSG/AttribsConfig.h>

using namespace ge::sg;


AttribsConfigId AttribsConfig::convertToId(const AttribsConfig& attribsConfig)
{
   unsigned configSize=attribsConfig.size();
   if(configSize>5||configSize<=1)
      return 0;

   uint16_t r=0;
   AttribType t;

   // indices
   //
   // Use of indices is signalled by ebo boolean.
   // If they are used, they required EBO to use UNSIGNED_INT type.
   //
   // Indices occupy bit 10 of the returned integer.
   if(attribsConfig.ebo)  r|=0x400;

   // coordinates
   //
   // Coordinates are expected to be at attribute index 0
   // and we expect that they are always specified.
   //
   // Coordinates occupies bits 0 and 1 of the returned integer.
   t=attribsConfig[0];
   if(t==AttribType::Vec3)  r|=0x1;
   else if(t==AttribType::Vec4)  r|=0x2;
   else if(t==AttribType::Vec2)  r|=0x3;
   else return 0;
   if(configSize==2)
      return r;

   // texCoords
   //
   // Texture coordinates are not mandatory.
   // We expect that they are stored at the last attribute index
   // (last index in AttribsConfig is occupied by indices flag,
   // so it is just before it).
   //
   // TexCoords occupies bits 8 and 9 of the returned integer.
   unsigned texCoordPossibleIndex=configSize-2;
   t=attribsConfig[texCoordPossibleIndex];
   if(t==AttribType::Empty);
   else if(t==AttribType::Vec2)  r|=0x100;
   else if(t==AttribType::HVec2)  r|=0x200;
   else texCoordPossibleIndex=0;
   if(configSize==3&&texCoordPossibleIndex!=0)
      return r;
   int numToParse=configSize-2;
   if(texCoordPossibleIndex!=0)
      numToParse--;

   // normals
   //
   // Normals are not mandatory.
   // If we find some 3-component formats,
   // let's consider them normals, although they may by colors as well.
   //
   // Normals occupies bits 2 and 3 of the returned integer.
   bool normalsFound=true;
   t=attribsConfig[1];
   if(t==AttribType::Empty);
   else if(t==AttribType::Vec3)  r|=0x4;
   else if(t==AttribType::HVec3)  r|=0x8;
   else if(t==AttribType::UBVec3)  r|=0xc;
   else normalsFound=false;
   if(normalsFound) {
      numToParse--;
      if(numToParse==0)
         return r;
   }

   // color
   //
   // Colors are not mandatory. If they are specified, they have to use attribute index 1 or 2.
   // Index 1 must be used if there are no normals, index 2 must be used when normals are in use.
   //
   // Color occupies bits 4,5 and 6 of the returned integer.
   t=attribsConfig[normalsFound?2:1];
   if(t==AttribType::Empty);
   else if(t==AttribType::Vec3)  r|=0x10;
   else if(t==AttribType::Vec4)  r|=0x20;
   else if(t==AttribType::HVec3)  r|=0x30;
   else if(t==AttribType::HVec4)  r|=0x40;
   else if(t==AttribType::UBVec3)  r|=0x50;
   else if(t==AttribType::UBVec4)  r|=0x60;
   //else if(t==Array::makeType(ArrayAdapter::GLType::UNSIGNED_INT_8_8_8_8,1)  r|=0x1c0;
   //else if(t==Array::makeType(ArrayAdapter::GLType::UNSIGNED_INT_8_8_8_8_REV,1)  r|=0x200;
   //else if(t==Array::makeType(ArrayAdapter::GLType::UNSIGNED_BYTE,ArrayAdapter::BGRA)  r|=0x240;
   else return 0;

   return r;
}


// AttribsConfigId type documentation
// note: brief description is with the variable declaration
/** \var AttribsConfigId
 *
 *  Complete attribute configuration is stored in AttribsConfig class,
 *  a complicated vector-based type.
 *  Using it for map lookups or comparison of two configurations
 *  might be performance expensive.
 *  Thus, frequently used attribute configurations has their
 *  integer-based representation that can be used for faster maps lookups
 *  and very fast comparison. This integer-based configuration uses
 *  type defined by AttribsConfigId.
 *
 *  Zero value stored in this type means that the attribute configuration
 *  is not one of the supported frequently used attribute configuration.
 *
 *  \sa AttribsConfig
 */

// AttribsConfig::configId documentation
// note: brief description is with the variable declaration
/** \var AttribsConfigId AttribsConfig::configId
 *
 *  If it is non-zero, AttribsConfig class contains one of known frequently used
 *  attribute configurations. Thus, optimized routines may be used for
 *  operations with attribute configurations such as comparison or lookups,
 *  as it is just comparison of integers or lookup by integer.
 *
 *  If the value is zero, all operations with attribute configurations
 *  have to be performed using AttribsConfig class that contains vector
 *  of values storing details about each particular attribute configuration.
 *
 *  If one AttribsStorage has _attribConfig zero and the second non-zero,
 *  they always contain different attribute configurations.
 */
