
#ifndef _cangle_h
#define _cangle_h 	1

#include "global_defs.h"
#include "cproperty.h"

class cGraph;
class cNode;

/**
  * @brief Represents an angle within a graph
  */
class cAngle {
public:
   /**
     * @brief Constructs an angle with two nodes
     * an angle has a name and connects to nodes (source and target)
     * @param name Name of the angle
     * @param source Source node
     * @param target Target node
     */	
   cAngle(cGraph * graph, const char * name, cNode * source, cNode * target);
   virtual ~cAngle();
   /**
     * @brief Returns the name of the angle
     */	
   inline STRING_T Name()
   {
      return _Name;
   };
   /**
     * @brief Returns the source node of the angle
     */	
   inline cNode * Source()
   {
      return _Source;
   };
   /**
     * @brief Returns the target node of the angle
     */	
   inline cNode * Target()
   {
      return _Target;
   };
   /**
     * @brief Method to add a property to an angle
     * A property is supplied as name value pair.
     * @param name Name of the property
     * @param value Value of the property
     */	
   void AddProperty(const char * name, const char * value);
   /**
     * @brief Method to pretty print angle information.
     * @param stream FILE pointer for the file to print into
     */	
   virtual void Print(FILE * stream, int level);
   /**
     * @brief Method to add an XML representation of the angle
     * @param text string reference to receive xml data. XML data of the node
     * will be added to the supplied string.
     * @param level used for identation
     */	
   virtual void XML(STRING_T & text, int level = 0);
protected:
   cGraph * _Graph;
   STRING_T _Name;   
   cNode * _Source;
   cNode * _Target;
   PROPERTY_VECTOR_T _Properties;
};

typedef std::vector<cAngle*> ANGLE_VECTOR_T;

#endif

