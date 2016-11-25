
#ifndef _cnode_h
#define _cnode_h 	1

#include "global_defs.h"
#include "cangle.h"
#include "cproperty.h"

class cNode;
typedef std::vector<cNode*> NODE_VECTOR_T;
typedef std::map<STRING_T,cNode*> GRAPH_NODE_MAP_T;

class cNode {
public:
   friend class cGraph;
private:
   cNode(cGraph * graph, const char * name);
   virtual ~cNode();
public:
   /**
     * @brief Returns the name of the node
     */	
   inline STRING_T Name()
   {
      return _Name;
   };
   /**
     * @brief Determines if this node is the root node of the graph
     */	
   bool IsRoot();
   /**
     * @brief Method to add an angle to a node
     * @param angle Pointer to the angle to be added.
     */	
   void AddAngle(cAngle * angle);
   /**
     * @brief Method to add a property to an node
     * A property is supplied as name value pair.
     * @param name Name of the property
     * @param value Value of the property
     */	
   void AddProperty(const char * name, const char * value);
   /**
     * @brief Method to pretty print node information.
     * @param stream FILE pointer for the file to print into
     */	
   virtual void Print(FILE * stream, int level);
   /**
     * @brief Method to add an XML representation of the node
     * @param text string reference to receive xml data. XML data of the node
     * will be added to the supplied string.
     * @param level used for identation
     */	
   virtual void XML(STRING_T & text, int level = 0);
   static void PrintLevel(FILE * stream, int level);
   static void PrintLevel(STRING_T & text, int level);
protected:
   cGraph * _Graph;
   STRING_T _Name;
   ANGLE_VECTOR_T _Angles;
   PROPERTY_VECTOR_T _Properties;
};

#endif

