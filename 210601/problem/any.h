#ifndef ANY_H_
#define ANY_H_

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace cls_26 {

struct any {
private:
    struct any_data_base {
        virtual ~any_data_base() {
        }
        virtual const std::type_info &type() const noexcept = 0;
        virtual std::unique_ptr<any_data_base> clone() const = 0;
        virtual void *data() noexcept = 0;
        virtual const void *data() const noexcept = 0;
    };

    std::unique_ptr<any_data_base> data;

    template <typename T>
    struct any_data : any_data_base {
    private:
        T object;
    };
};

}  // namespace cls_26

#endif  // ANY_H_
