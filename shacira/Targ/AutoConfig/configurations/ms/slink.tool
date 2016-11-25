

.command_line link -nologo -dll $(link_options) -pdb:$(intermediate_dir)/$(target_name).pdb -out:$(intermediate_dir) -out:$@ $(objects) $(libraries) $(library_dirs)
