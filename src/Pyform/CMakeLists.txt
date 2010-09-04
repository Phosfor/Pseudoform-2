#########Pyform############
set(Pyform_src
    Pyform.cpp
)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(Pyform SHARED
    ${Pyform_src}
)

target_link_libraries(Pyform
    python2.6
    boost_python
    Pseudoform
    #${Boost_LIBRARIES}
    #${SFML_LIBRARY}
    #${OGRE_LIBRARIES}
    #${BULLET_LIBRARIES}
    #${MYGUI_LIBRARIES}
    #${MYGUI_PLATFORM_LIBRARIES}
    #${OIS_LIBRARIES}
)


