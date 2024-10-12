#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #include <io.h> 
  #define access _access 
#else 
 #include <unistd.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// ASCII characters based on pixel brightness
const char *ASCII_CHARS = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:\"^`'. ";

// Constants for image and video processing
#define FRAME_PREFIX "frame_"
#define FRAME_EXTENSION ".png"
#define FRAME_FORMAT FRAME_PREFIX "%04d" FRAME_EXTENSION

// Function to check if the file has a valid extension
int validate_file_extension(const char *file_path) {
    const char *valid_extensions[] = {".png", ".jpg", ".jpeg", ".gif", ".mov", ".mp4"};
    const char *file_extension = strrchr(file_path, '.');

    if (file_extension) {
        for (int i = 0; i < sizeof(valid_extensions) / sizeof(valid_extensions[0]); i++) {
            if (strcmp(file_extension, valid_extensions[i]) == 0) {
                return 1; // Valid extension found
            }
        }
    }
    return 0; // Invalid extension
}

// Function to map pixel brightness to an ASCII character
char brightness_to_ascii(int brightness) {
    int index = brightness * (strlen(ASCII_CHARS) - 1) / 255;
    return ASCII_CHARS[index < 0 ? 0 : (index >= strlen(ASCII_CHARS) ? strlen(ASCII_CHARS) - 1 : index)];
}

// Function to process the image and convert it to ASCII
void process_image_to_ascii(const char *image_path, const char *output_path) {
    printf("Processing the image: %s\n", image_path);

    int width, height, channels;
   unsigned char *img = stbi_load(image_path, &width, &height, &channels, 0);
    if (!img) {
        fprintf(stderr, "Error: Failed to load image: %s\n", image_path);
        return;
    }

    // Open the output file
    FILE *output_file = fopen(output_path, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Failed to open output file: %s\n", output_path);
        stbi_image_free(img);
        return;
    }

    // Loop through each pixel in the image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel_index = (y * width + x) * channels;
            int r = img[pixel_index];
            int g = img[pixel_index + 1];
            int b = img[pixel_index + 2];

            // Calculate brightness using perceived brightness formula
            int brightness = (int)(0.2126 * r + 0.7152 * g + 0.0722 * b);

            // Convert brightness to ASCII character and print
            fputc(brightness_to_ascii(brightness), output_file);
        }
        fputc('\n', output_file); // New line after each row
    }

    fclose(output_file); // Close the output file
    stbi_image_free(img); // Free the image memory
    printf("Image conversion to ASCII complete. Output saved to %s\n", output_path);
}

// Function to process video files using FFmpeg and convert them to ASCII
void process_video_to_ascii(const char *video_path, const char *output_directory) {
    printf("Processing the video: %s\n", video_path);

    // Extract frames using FFmpeg (1 frame per second for simplicity)
    char command[512];
    snprintf(command, sizeof(command), "ffmpeg -i \"%s\" -vf fps=1 %s", video_path, FRAME_FORMAT);
    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to extract frames from video: %s\n", video_path);
        return;
    }

    // Process each extracted frame dynamically
    for (int i = 1; ; i++) {
        char frame_path[256];
        snprintf(frame_path, sizeof(frame_path), FRAME_FORMAT, i);
        
        // Check if the frame exists before processing
       #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// ASCII characters based on pixel brightness
const char *ASCII_CHARS = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:\"^`'. ";

// Constants for image and video processing
#define FRAME_PREFIX "frame_"
#define FRAME_EXTENSION ".png"
#define FRAME_FORMAT FRAME_PREFIX "%04d" FRAME_EXTENSION

// Function to check if the file has a valid extension
int validate_file_extension(const char *file_path) {
    const char *valid_extensions[] = {".png", ".jpg", ".jpeg", ".gif", ".mov", ".mp4"};
    const char *file_extension = strrchr(file_path, '.');

    if (file_extension) {
        for (int i = 0; i < sizeof(valid_extensions) / sizeof(valid_extensions[0]); i++) {
            if (strcmp(file_extension, valid_extensions[i]) == 0) {
                return 1; // Valid extension found
            }
        }
    }
    return 0; // Invalid extension
}

// Function to map pixel brightness to an ASCII character
char brightness_to_ascii(int brightness) {
    int index = brightness * (strlen(ASCII_CHARS) - 1) / 255;
    return ASCII_CHARS[index < 0 ? 0 : (index >= strlen(ASCII_CHARS) ? strlen(ASCII_CHARS) - 1 : index)];
}

// Function to process the image and convert it to ASCII
void process_image_to_ascii(const char *image_path) {
    printf("Processing the image: %s\n", image_path);

    int width, height, channels;
    unsigned char *img = stbi_load(image_path, &width, &height, &channels, 0);
    if (!img) {
        fprintf(stderr, "Error: Failed to load image: %s\n", image_path);
        return;
    }

    // Loop through each pixel in the image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel_index = (y * width + x) * channels;
            int r = img[pixel_index];
            int g = img[pixel_index + 1];
            int b = img[pixel_index + 2];

            // Calculate brightness using perceived brightness formula
            int brightness = (int)(0.2126 * r + 0.7152 * g + 0.0722 * b);

            // Convert brightness to ASCII character and print
            printf("%c", brightness_to_ascii(brightness));
        }
        printf("\n"); // New line after each row
    }

    stbi_image_free(img); // Free the image memory
    printf("Image conversion to ASCII complete.\n");
}

// Function to process video files using FFmpeg and convert them to ASCII
void process_video_to_ascii(const char *video_path) {
    printf("Processing the video: %s\n", video_path);

    // Extract frames using FFmpeg (1 frame per second for simplicity)
    char command[512];
    snprintf(command, sizeof(command), "ffmpeg -i \"%s\" -vf fps=1 %s", video_path, FRAME_FORMAT);
    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to extract frames from video: %s\n", video_path);
        return;
    }

    // Process each extracted frame dynamically
    for (int i = 1;; i++) {
        char frame_path[256];
        snprintf(frame_path, sizeof(frame_path), FRAME_FORMAT, i);

        // Check if the frame exists before processing (using fopen)
        FILE *file = fopen(frame_path, "r");
        if (file) {
            fclose(file); // Close the file if it exists
            process_image_to_ascii(frame_path); // Convert each frame to ASCII
        } else {
            printf("No more frames to process. Stopping at frame: %s\n", frame_path);
            break; // Stop if no more frames exist
        }
    }

    printf("Video conversion to ASCII complete.\n");
}

// Main function to prompt the user and process multimedia files
int main() {
    char file_path[256];

    // Prompt user for file path
    printf("Enter the path of the image/video file (png/jpg/jpeg/gif/mov/mp4): ");
    if (scanf("%255s", file_path) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    // Validate the file extension
    if (validate_file_extension(file_path)) {
        printf("Valid file: %s\n", file_path);

        // Check if the file is a video or image
        const char *file_extension = strrchr(file_path, '.');
        if (strcmp(file_extension, ".mp4") == 0 || strcmp(file_extension, ".mov") == 0 || strcmp(file_extension, ".gif") == 0) {
            process_video_to_ascii(file_path); // Process video or GIF file
        } else {
            process_image_to_ascii(file_path); // Process image file
        }

        printf("Processing complete.\n");
    } else {
        fprintf(stderr, "Invalid file type. Please provide a valid image or video file.\n");
    }

    return 0;
}

    }

    // Clean up extracted frames
    for (int i = 1; ; i++) {
        char frame_path[256];
        snprintf(frame_path, sizeof(frame_path), FRAME_FORMAT, i);
        if (access(frame_path, F_OK) != 0) {
            break; // Stop if no more frames exist
        }
        remove(frame_path); // Remove the frame file
    }

    printf("Video conversion to ASCII complete.\n");
}

// Main function to prompt the user and process multimedia files
int main() {
    char file_path[256];
    char output_path[256];

    // Prompt user for file path
    printf("Enter the path of the image/video file (png/jpg/jpeg/gif/mov/mp4): ");
    if (scanf("%255s", file_path) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    // Validate the file extension
    if (validate_file_extension(file_path)) {
        printf("Valid file: %s\n", file_path);

        // Prompt user for output file location
        printf("Enter the output file location for ASCII art (without extension): ");
        if (scanf("%255s", output_path) != 1) {
            fprintf(stderr, "Error: Invalid output path.\n");
            return 1;
        }

        // Check if the file is a video or image
        const char *file_extension = strrchr(file_path, '.');
        if (strcmp(file_extension, ".mp4") == 0 || strcmp(file_extension, ".mov") == 0 || strcmp(file_extension, ".gif") == 0) {
            process_video_to_ascii(file_path, output_path); // Process video or GIF file
        } else {
            char ascii_output[256];
            snprintf(ascii_output, sizeof(ascii_output), "%s.txt", output_path);
            process_image_to_ascii(file_path, ascii_output); // Process image file
        }

        printf("Processing complete.\n");
    } else {
        fprintf(stderr, "Invalid file type. Please provide a valid image or video file.\n");
    }

    return 0;
}
