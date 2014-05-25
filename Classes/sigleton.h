//
//  sigleton.h
//  puke
//
//  Created by zcw on 14-5-25.
//
//

#ifndef puke_sigleton_h
#define puke_sigleton_h

template <typename T>
class sigleton {
    sigleton(){};
    
public:
    static T* instance(){
        static T myT;
        return &myT;
    }
};

#endif
