// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_MACROS_H_
#define REZERO_BASE_MACROS_H_

#define REZERO_DISALLOW_COPY(TypeName) TypeName(const TypeName&) = delete

#define REZERO_DISALLOW_ASSIGN(TypeName) \
  TypeName& operator=(const TypeName&) = delete

#define REZERO_DISALLOW_MOVE(TypeName) \
  TypeName(TypeName&&) = delete;       \
  TypeName& operator=(TypeName&&) = delete

#define REZERO_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;             \
  TypeName& operator=(const TypeName&) = delete

#define REZERO_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName) \
  TypeName(const TypeName&) = delete;                  \
  TypeName& operator=(const TypeName&) = delete;       \
  TypeName(TypeName&&) = delete;                       \
  TypeName& operator=(TypeName&&) = delete

#define REZERO_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName() = delete;                                  \
  REZERO_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName)

#endif // REZERO_BASE_MACROS_H_