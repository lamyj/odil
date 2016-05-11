# Group files by their folder
macro(GroupFiles fileGroup)
    # Beautify fileGroup (HEADER_FILES -> Header Files)
    string(REPLACE "_" " " fileGroupName ${fileGroup})	# Replace underscores with spaces
    string(TOLOWER ${fileGroupName} fileGroupName)		# To lower
    set(finalFileGroupName)
    string(REGEX MATCHALL "([^ ]+)" fileGroupNameSplit ${fileGroupName}) # Split each word
    foreach(fileGroupNameWord ${fileGroupNameSplit})	# Set to upper the first letter of each word
        string(SUBSTRING ${fileGroupNameWord} 0 1 firstLetter)
        string(SUBSTRING ${fileGroupNameWord} 1 -1 otherLetters)
        string(TOUPPER ${firstLetter} firstLetter)
        if(finalFileGroupName)
            set(finalFileGroupName "${finalFileGroupName} ")
        endif()
        set(finalFileGroupName "${finalFileGroupName}${firstLetter}${otherLetters}")
    endforeach()

    # Put each file in the correct group
    foreach(currentFile ${${fileGroup}})
        set(folder ${currentFile})
        get_filename_component(filename ${folder} NAME) # Get the file name
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" folder ${folder})	# Get the folder relative to the current one
        string(REPLACE "${filename}" "" folder ${folder})					# Remove the file name
        set(groupName "${finalFileGroupName}")
        if(NOT folder STREQUAL "") # Parse the remaining directories hierarchy
            string(REGEX REPLACE "/+$" "" baseFolder ${folder}) # Remove trailing slash
            string(REPLACE "/" "\\" baseFolder ${baseFolder})	# Forward to backward slashes
            set(groupName "${groupName}\\${baseFolder}")		# Put together the entire group name
        endif()
        source_group("${groupName}" FILES ${currentFile})		# Put the file in this group
    endforeach()
endmacro()