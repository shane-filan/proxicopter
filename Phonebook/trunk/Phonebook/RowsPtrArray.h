#pragma once

template <class ROW_TYPE> class CRowsPtrArray: public CTypedPtrArray<CPtrArray, ROW_TYPE*>
{
public:
  ~CRowsPtrArray(void)
  {
    for(int i = 0; i < GetCount(); i++)
    {
      delete GetAt(i);
    }
    RemoveAll();
  };
};
