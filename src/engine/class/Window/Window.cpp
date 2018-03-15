#include "Window.hpp"

sf::RenderWindow* Window::getContext () {

    return m_context.get();

}

bool Window::exists () {

    if (m_context) {
        return true;
    }

    return false;

}

bool Window::isOpen () {

    if (Window::exists() && m_context->isOpen()) {
        return true;
    }

    return false;

}

void Window::open () {

    if (Window::exists()) {
        Log::warning("Window cannot be opened because it is already open.");
        return;
    }

    m_context = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(m_width, m_height),
        m_title,
        sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar
    );

    if (!m_context) {
        Log::error("Failed to create a window.");
        return;
    }

    Log::verbose("Window opened.");

}

void Window::close () {

    if (!Window::isOpen()) {
        Log::warning("Window cannot be closed because it is not open.");
    }

    Log::verbose("Closing window.");
    m_context->close();
    if (m_context) {
        m_context.reset();
    }

}

void Window::display () {

    if (!Window::exists()) {
        Log::warning("Cannot display window because it is not open.");
        return;
    }

    m_context->display();

}

void Window::draw (const sf::Drawable& drawable, const sf::RenderStates& states) {

    m_context->draw(drawable, states);

}

void Window::clear () {

    if (!Window::exists()) {
        Log::warning("Cannot clear window because it is not open.");
        return;
    }

    m_context->clear();

}

void Window::clear (sf::Color color) {

    if (!Window::exists()) {
        Log::warning("Cannot clear window because it is not open.");
    }

    m_context->clear(std::move(color));

}

bool Window::pollEvent (sf::Event& windowEvent) {

    return m_context->pollEvent(windowEvent);

}

int Window::getWidth () {

    return m_width;

}

int Window::getHeight () {

    return m_height;

}

void Window::setWidth (int width) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_width = std::move(width);
    pushWindowSize();

}

void Window::setHeight (int height) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_height = std::move(height);
    pushWindowSize();

}

void Window::setSize (int width, int height) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_width = std::move(width);
    m_height = std::move(height);
    pushWindowSize();

}

std::string Window::getTitle () {

    return m_title;

}

void Window::setTitle (std::string title) {

    std::unique_lock<std::mutex> lock_title(mutex_title);

    m_title = std::move(title);
    pushWindowTitle();

}

void Window::pushWindowSize () {

    if (m_context) {
        m_context->setSize(sf::Vector2u(m_width, m_height));
    }

}

void Window::pushWindowTitle () {

    if (m_context) {
        m_context->setTitle(sf::String(m_title));
    }

}

std::unique_ptr<sf::RenderWindow> Window::m_context;

int Window::m_width = 800;
int Window::m_height = 600;
std::mutex Window::mutex_size;

std::string Window::m_title = "";
std::mutex Window::mutex_title;