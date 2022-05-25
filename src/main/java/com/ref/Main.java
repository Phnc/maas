package com.ref;

import com.change_vision.jude.api.inf.AstahAPI;
import com.change_vision.jude.api.inf.exception.*;
import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.project.ModelFinder;
import com.change_vision.jude.api.inf.project.ProjectAccessor;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws ProjectNotFoundException, ProjectLockedException, LicenseNotFoundException, IOException, ClassNotFoundException, NonCompatibleException, InvalidExportImageException, InvalidUsingException {
        ProjectAccessor projectAccessor = AstahAPI.getAstahAPI().getProjectAccessor();
        projectAccessor.open("src/main/resources/action1.asta");
        INamedElement[] findElements = findElements(projectAccessor);

        IActivityDiagram ad = (IActivityDiagram) findElements[0];
        String name = ad.getActivity().getName();
        ad.exportImage("src/main/resources/" + name, "png", 96);


    }

    public static INamedElement[] findElements(ProjectAccessor projectAccessor) throws ProjectNotFoundException {
        INamedElement[] foundElements = projectAccessor.findElements(new ModelFinder() {
            public boolean isTarget(INamedElement namedElement) {
                return namedElement instanceof IActivityDiagram;
            }
        });
        return foundElements;
    }
}
