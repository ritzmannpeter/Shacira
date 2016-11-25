
#include "Tools/utilities/utilities.h"
#include "Tools/utilities/cStringSink.h"

static void ParseStringFile(const char * input_file_name, const char * output_file_name)
{
   cStringSink sink;
   sink.LoadStringFile(output_file_name);
   sink.LoadStringFile(input_file_name);
   sink.SaveStringFile(output_file_name);
}
   
static void PrintUsage()
{
   printf("usage: text -i<input_file> -o<output_file>\n");
}

int main(int argc, char* argv[])
{
   if (argc < 2) {
      PrintUsage();
      return -1;
   }
   const char * input_file_name = NULL;
   const char * output_file_name = NULL;
   for (int i=0; i<argc; i++) {
      if (strncmp(argv[i], "-i", 2) == 0) {
         input_file_name = GetArg(i, argc, argv, 2);
      } else if (strncmp(argv[i], "-o", 2) == 0) {
         output_file_name = GetArg(i, argc, argv, 2);
      }
   }
   if (input_file_name == NULL) {
      printf("missing input file name\n");
      PrintUsage();
      return -1;
   }
   if (input_file_name == NULL) {
      printf("missing output file name\n");
      PrintUsage();
      return -1;
   }

   ParseStringFile(input_file_name, output_file_name);
   return 0;
}

